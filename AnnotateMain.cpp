/*
 * AnnotateMain.cpp
 *
 *  Created on: Apr 2, 2013
 *      Author: zxwang
 */

#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>
#include <list>
#include <opencv2/opencv.hpp>
#include <vector>

bool is_draw = false;
int start_x, start_y;
cv::Mat image;
std::list<cv::Rect> rect_vector;

void draw_string(cv::Mat& img, const std::string& text) {
	cv::Size size = cv::getTextSize(text, cv::FONT_HERSHEY_COMPLEX, 0.6f, 1,
			NULL);
	cv::putText(img, text, cv::Point(0, size.height), cv::FONT_HERSHEY_COMPLEX,
			0.6f, CV_RGB(200,50,50), 1, CV_AA);
}

void mouse_callback(int event, int x, int y, int flags, void* param) {
	switch (event) {
	case CV_EVENT_MOUSEMOVE:
		if (is_draw) {
			cv::Mat copy = image.clone();
			int size = std::max(abs(x - start_x), abs(y - start_y));
			cv::rectangle(copy, cv::Point(start_x, start_y),
					cv::Point(start_x + size, start_y + size),
					cv::Scalar(0, 0, 255, 0), 2, CV_AA);
			cv::imshow("annotate", copy);
		}
		break;
	case CV_EVENT_LBUTTONDOWN:
		start_x = x;
		start_y = y;
		is_draw = true;
		break;
	case CV_EVENT_LBUTTONUP:
		is_draw = false;
		break;
	}
}

// this executable is to generate positive samples to train the cascade classifier
int main(int argc, char* argv[]) {
	if (argc == 1) {
		std::cout << "Usage: ./annotate video-file output-dir" << std::endl;
		return 0;
	}
	cv::VideoCapture capture(argv[1]);
	boost::filesystem::create_directories(argv[2]);
	int index = 0;
	cv::namedWindow("annotate");
	cv::setMouseCallback("annotate", mouse_callback, NULL);
	if (capture.isOpened()) {
		while (true) {
			capture >> image;
			if (image.empty()) {
				break;
			}
			cv::imshow("annotate", image);
			int key = cv::waitKey();
			if (key == 'q') {
				break;
			}
		}
	}
	capture.release();
	return 0;
}
