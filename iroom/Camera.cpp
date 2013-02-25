#include "Camera.h"

std::mutex Camera::s_av_mutex;

Camera::~Camera(void)
{
	curl_easy_cleanup(m_curl_handle);
}

// producer wrapper
size_t Camera::invoke_frame_producer(void* ptr, size_t size, size_t nmemb, void* p_instance){
	return ((Camera*)p_instance)->frame_producer(ptr, size, nmemb);
}

// producer function. put each fetched image to the queue.
size_t Camera::frame_producer(void* ptr, size_t size, size_t nmemb){
	size_t len = size * nmemb;
	unsigned char* c_ptr = (unsigned char*)ptr;
	cv::Mat image = generate_frame(c_ptr, len);
	if(!image.empty()){
		std::unique_lock<std::mutex> lock(m_queue_mutex);
		m_buffer_queue.push(image);
		m_condition_var.notify_one();
	}	
	return len;
}

// search data block for SOI and EOI.
cv::Mat Camera::generate_frame(unsigned char* c_ptr, size_t len){
	cv::Mat image;
	bool start = false;
	bool end = false;
	unsigned char* soi_ptr = c_ptr; 
	unsigned char* eoi_ptr = c_ptr + len;
	for(size_t i = 0; i < len - 1; ++i){
		if(c_ptr[i] == 0xFF){
			if(c_ptr[i+1] == 0xD8){
				soi_ptr = c_ptr + i;
				start = true;
			}
			if(c_ptr[i+1] == 0xD9){
				eoi_ptr = c_ptr + i;
				end = true;
			}
		}
	}
	if(start && end){
		if(soi_ptr < eoi_ptr){
			m_buffer.assign(soi_ptr, eoi_ptr); // start before end.
		}else{
			std::copy(c_ptr, eoi_ptr, std::back_inserter(m_buffer)); // end before start.
			image = cv::imdecode(m_buffer, 1);
			m_buffer.assign(soi_ptr, c_ptr + len); // start a new frame
		}
	}else if(start){
		m_buffer.assign(soi_ptr, eoi_ptr);
	}else if(!m_buffer.empty()){
		std::copy(soi_ptr, eoi_ptr, std::back_inserter(m_buffer));
		if(end){
			image = cv::imdecode(m_buffer, 1);
		}
	}
	return image;
}

Camera::Camera(const std::string& ip_address, const std::string& username, const std::string& password) : m_ip_address(ip_address), m_username(username), m_password(password), m_curl_handle(NULL), m_stop(true){
	std::string userpass = m_username + ":" + m_password;
	m_curl_handle = curl_easy_init();
	curl_easy_setopt(m_curl_handle, CURLOPT_USERPWD, userpass.c_str());
}

void Camera::capture(const std::string& frame_path, const std::string& timestamp_path, int n){
	m_frame_path = frame_path;
	m_timestamp_path = timestamp_path;
	m_stop = false;
	s_av_mutex.lock(); // make libav happy in multithreading.
	m_video_writer.open(m_frame_path, CV_FOURCC('M','P','4','2'), 30, cv::Size(640, 480)); // output video format.
	s_av_mutex.unlock();
	m_timestamp_stream.open(m_timestamp_path);
	if(m_video_writer.isOpened() && m_timestamp_stream.good()){
		// create a thread for producer
		std::thread producer([&]{
			std::string url = "http://" + m_ip_address + "/nphMotionJpeg?Resolution=640x480&Quality=Clarity";
			curl_easy_setopt(m_curl_handle, CURLOPT_URL, url.c_str());
			curl_easy_setopt(m_curl_handle, CURLOPT_WRITEDATA, this);
			curl_easy_setopt(m_curl_handle, CURLOPT_WRITEFUNCTION, invoke_frame_producer);
			curl_easy_setopt(m_curl_handle, CURLOPT_TIMEOUT, n); // set timeout
			curl_easy_perform(m_curl_handle);
			// stop the consumer
			m_stop = true;
		});
		// create a thread for consumer
		std::thread consumer([&]{
			cv::namedWindow(m_ip_address);
			while(!m_stop){
				std::unique_lock<std::mutex> lock(m_queue_mutex);
				m_condition_var.wait_for(lock, std::chrono::seconds(1), [&]{return !m_buffer_queue.empty();}); // guard against spurious wakeups
				if(!m_buffer_queue.empty()){
					cv::Mat image = m_buffer_queue.front();
					save_frame(image);
					cv::imshow(m_ip_address, image);
					cv::waitKey(30);
					m_buffer_queue.pop();
				}
			}
			cv::destroyWindow(m_ip_address);
		});
		producer.join();
		consumer.join();
		m_timestamp_stream.close();
	}
}

void Camera::save_frame(const cv::Mat& image){
	auto duration = std::chrono::high_resolution_clock::now().time_since_epoch();
	m_timestamp_stream << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << std::endl; // write current timestamp.
	m_video_writer << image; // write image data.
}