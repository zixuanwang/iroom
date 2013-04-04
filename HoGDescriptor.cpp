/*
 * HoGDescriptor.cpp
 *
 *  Created on: Apr 3, 2013
 *      Author: zxwang
 */

#include "HoGDescriptor.h"

HoGDescriptor::HoGDescriptor(int num_bins) : m_num_bins(num_bins) {

}

HoGDescriptor::~HoGDescriptor() {

}

void HoGDescriptor::compute(cv::Mat& image, cv::Mat& mask){
}

void HoGDescriptor::compute_gradient(cv::Mat& image, cv::Mat& magnitude, cv::Mat& angle, std::vector<float>& histogram){
	magnitude = cv::Mat(image.size(), CV_32FC1, cv::Scalar(0.f));
	angle = cv::Mat(image.size(), CV_32FC1, cv::Scalar(0.f));
	histogram.assign(m_num_bins, 0.f);
	cv::Mat gray = image;
	if(image.type() == CV_8UC3){
		cv::cvtColor(image, gray, CV_BGR2GRAY);
	}
	for(int row = 0; row < image.rows - 1; ++row){
		uchar* row_ptr = gray.ptr<uchar>(row);
		uchar* row_ptr_next = gray.ptr<uchar>(row + 1);
		float* mag_row_ptr = magnitude.ptr<float>(row);
		float* angle_row_ptr = angle.ptr<float>(row);
		for(int col = 0; col < image.cols - 1; ++col){
			float dx = static_cast<float>(row_ptr[col + 1]) - static_cast<float>(row_ptr[col]);
			float dy = static_cast<float>(row_ptr_next[col]) - static_cast<float>(row_ptr[col]);
			float mag = sqrtf(dx * dx + dy * dy);
			float ang = 0.f;
			if(dx != 0.f || dy != 0.f)
				ang = atanf(dy / dx);
			mag_row_ptr[col] = mag;
			angle_row_ptr[col] = ang;
			int bin_index = m_num_bins * (ang / PI +  0.5f);
			//std::cout << bin_index << std::endl;
			if(bin_index == m_num_bins){
				bin_index = m_num_bins - 1;
			}
			histogram[bin_index] += mag;
		}
	}
	Utility::l2_normalize(histogram);
}
