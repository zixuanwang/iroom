/*
 * AnalyserMain.cpp
 *
 *  Created on: Apr 2, 2013
 *      Author: zxwang
 */

#include <algorithm>
#include <boost/lexical_cast.hpp>
#include "ColorDescriptor.h"
#include "HoGDescriptor.h"
#include "MotionDescriptor.h"
#include <opencv2/opencv.hpp>
#include "Utility.h"

void test_harr_upperbody(){
	cv::VideoCapture capture("/home/zxwang/Dropbox/data/iroom/video1/171.67.83.73.avi");
	cv::CascadeClassifier classifier;
	classifier.load("/usr/local/share/OpenCV/haarcascades/haarcascade_mcs_upperbody.xml");
	cv::namedWindow("capture");
	if(capture.isOpened()){
		while(true){
			cv::Mat image;
			cv::Mat gray;
			capture >> image;
			if(image.empty())
				break;
			cv::cvtColor(image, gray, CV_BGR2GRAY);
			std::vector<cv::Rect> people_array;
			classifier.detectMultiScale(gray, people_array);
			std::for_each(people_array.begin(), people_array.end(), [&image](cv::Rect& rect){cv::rectangle(image, rect, cv::Scalar(0,0,220,0), 2, CV_AA);});
			cv::imshow("capture", image);
			cv::waitKey(30);
		}
	}
	capture.release();
}

void test_feature(){
	cv::VideoCapture capture("/home/zxwang/Dropbox/data/iroom/video1/171.67.83.73.avi");
	cv::namedWindow("capture");
	ColorDescriptor color;
	HoGDescriptor hog;
	MotionDescriptor motion;
	if(capture.isOpened()){
		while(true){
			cv::Mat image;
			cv::Mat mask;
			cv::Mat background;
			cv::Mat flow;
			std::vector<float> histogram;
			capture >> image;
			if(image.empty())
				break;
			//color.update_background(image, mask);
			//color.get_background(background);
			//hog.compute_gradient(image, histogram);
			motion.compute(image, flow);
			motion.draw_optical_flow(flow, image, 16);
			cv::imshow("capture", image);
			cv::waitKey(30);
		}
	}
	capture.release();
}

int main(int argc, char* argv[]){
	test_feature();
	return 0;
}


