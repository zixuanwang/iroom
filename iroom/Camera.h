#pragma once
#include <curl/curl.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_array.hpp>
#include <opencv2/opencv.hpp>
#include <queue>
#include <string>
#include <iostream>
#include <fstream>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <stdexcept>

class Camera
{
public:
	// construct the camera by passing the ip address, username and password.
	Camera(const std::string& ip_address, const std::string& username = "", const std::string& password = "");
	virtual ~Camera(void);
	void capture(const std::string& frame_path, const std::string& timestamp_path);
	std::string get_ip_address(){return m_ip_address;}
	std::string get_frame_path(){return m_frame_path;}
	std::string get_timestamp_path(){return m_timestamp_path;}
	static size_t invoke_frame_producer(void* ptr, size_t size, size_t nmemb, void* p_instance);
	size_t Camera::frame_producer(void* ptr, size_t size, size_t nmemb);
	cv::Mat generate_image(unsigned char* c_ptr, size_t len);
private:
	std::string m_ip_address;
	std::string m_username;
	std::string m_password;
	CURL* m_curl_handle;
	std::string m_frame_path;
	std::string m_timestamp_path;
	std::ofstream m_frame_stream;
	std::ofstream m_timestamp_stream;
	std::vector<uchar> m_buffer;
	std::mutex m_queue_mutex;
	std::condition_variable m_condition_var;
	std::queue<cv::Mat> m_buffer_queue; // maintain the producer consumer queue.
	bool m_stop; // indicate whether to stop the capture.
};

