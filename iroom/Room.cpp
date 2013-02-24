#include "Room.h"


Room::Room(void)
{
	curl_global_init(CURL_GLOBAL_ALL);
	m_curl_multi_handle = curl_multi_init();
}


Room::~Room(void)
{
	curl_multi_cleanup(m_curl_multi_handle);
}

void Room::init(const std::string& config_path){
	std::ifstream in_stream;
	in_stream.open(config_path);
	if(in_stream.good()){
		std::string username;
		std::string password;
		// read username and password
		getline(in_stream, username);
		getline(in_stream, password);
		// read ip_address
		std::string ip_address;
		while(getline(in_stream, ip_address)){
			m_camera_array.push_back(std::shared_ptr<Camera>(new Camera(ip_address, username, password)));
		}
		in_stream.close();
	}
}

void Room::capture(const std::string& output_dir){
	std::vector<std::shared_ptr<std::thread> > thread_ptr_array;
	for(size_t i = 0; i < m_camera_array.size(); ++i){
		thread_ptr_array.push_back(std::shared_ptr<std::thread>(new std::thread([&, i](){
			std::string prefix = output_dir + "/" + m_camera_array[i]->get_ip_address();
			m_camera_array[i]->capture(prefix + ".frame", prefix + ".timestamp");
		})));
	}
	std::for_each(thread_ptr_array.begin(), thread_ptr_array.end(), [](std::shared_ptr<std::thread>& p){p->join();});
}