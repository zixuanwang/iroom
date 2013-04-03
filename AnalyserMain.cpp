/*
 * AnalyserMain.cpp
 *
 *  Created on: Apr 2, 2013
 *      Author: zxwang
 */

#include <algorithm>
#include <boost/lexical_cast.hpp>
#include <opencv2/opencv.hpp>
int main(int argc, char* argv[]){
	cv::VideoCapture capture("/home/zxwang/Dropbox/data/iroom/video1/171.67.83.73.avi");
	cv::CascadeClassifier classifier;
	classifier.load("/usr/local/share/OpenCV/haarcascades/haarcascade_mcs_upperbody.xml");
//	classifier.load("/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt2.xml");
	int index = 0;
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
			//cv::imwrite("/home/zxwang/Desktop/frame/171.67.88.36/" + boost::lexical_cast<std::string>(index++) + ".jpg", image);
		}
	}
	capture.release();
	return 0;
}


