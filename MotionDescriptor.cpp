/*
 * MotionDescriptor.cpp
 *
 *  Created on: Apr 3, 2013
 *      Author: zxwang
 */

#include "MotionDescriptor.h"

MotionDescriptor::MotionDescriptor() {

}

MotionDescriptor::~MotionDescriptor() {

}

void MotionDescriptor::draw_optical_flow(const cv::Mat& flow,
		cv::Mat& cflow_map, int step) {
	for (int y = 0; y < flow.rows; y += step) {
		for (int x = 0; x < flow.cols; x += step) {
			const cv::Point2f& fxy = flow.at<cv::Point2f>(y, x);
			line(cflow_map, cv::Point(x, y),
					cv::Point(cvRound(x + fxy.x), cvRound(y + fxy.y)), cv::Scalar(0, 0, 255));
			cv::circle(cflow_map, cv::Point(x, y), 2, cv::Scalar(0, 0, 255), -1);
		}
	}
}

void MotionDescriptor::compute(const cv::Mat& image, cv::Mat& flow){
	cv::Mat gray = image;
	if(image.type() == CV_8UC3){
		cv::cvtColor(image, gray, CV_BGR2GRAY);
	}
	if(!m_prev.empty())
		cv::calcOpticalFlowFarneback(m_prev, gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
	m_prev = gray.clone();
}
