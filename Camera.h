#pragma once
#include <boost/shared_array.hpp>
#include <chrono>
#include <condition_variable>
#include <curl/curl.h>
#include <fstream>
#include <iostream>
#include <mutex>
#include <opencv2/opencv.hpp>
#include <queue>
#include <stdexcept>
#include <string>
#include <thread>

class Camera
{
public:
	// construct the camera by passing the ip address, username and password.
	Camera(const std::string& ip_address, const std::string& username = "", const std::string& password = "");
	virtual ~Camera(void);
	void capture(const std::string& frame_path, const std::string& timestamp_path, int n = 0); // capture the video for n seconds.
	std::string get_ip_address(){return m_ip_address;}
	std::string get_frame_path(){return m_frame_path;}
	std::string get_timestamp_path(){return m_timestamp_path;}
	static size_t invoke_frame_producer(void* ptr, size_t size, size_t nmemb, void* p_instance);
	size_t frame_producer(void* ptr, size_t size, size_t nmemb);
	cv::Mat generate_frame(unsigned char* c_ptr, size_t len);
	void save_frame(const cv::Mat& image); // save image to m_video_writer and save the according timestamp to m_timestamp_stream. called from the consumer.
	CURL* get_curl_handle(){return m_curl_handle;}
private:
	std::string m_ip_address;
	std::string m_username;
	std::string m_password;
	CURL* m_curl_handle;
	std::string m_frame_path;
	std::string m_timestamp_path;
	cv::VideoWriter m_video_writer;
	std::ofstream m_timestamp_stream;
	std::vector<uchar> m_buffer;
	std::mutex m_queue_mutex;
	std::condition_variable m_condition_var;
	std::queue<cv::Mat> m_buffer_queue; // maintain the producer consumer queue.
	bool m_stop; // indicate whether to stop the capture.
	static std::mutex s_av_mutex;
};

