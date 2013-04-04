/*
 * Utility.cpp
 *
 *  Created on: Apr 3, 2013
 *      Author: zxwang
 */

#include "Utility.h"

Utility::Utility() {

}

Utility::~Utility() {

}

float Utility::l1_norm(const std::vector<float>& v){
	float sum = 0.f;
	std::for_each(v.begin(), v.end(), [&sum](float v){sum += v;});
	return sum;
}

float Utility::l2_norm(const std::vector<float>& v){
	float sum = 0.f;
	std::for_each(v.begin(), v.end(), [&sum](float v){sum += v * v;});
	return sqrtf(sum);
}

void Utility::l1_normalize(std::vector<float>& v){
	float norm = l1_norm(v);
	if(norm == 0.f){
		std::cerr << "0 norm" << std::endl;
		exit(1);
	}
	std::for_each(v.begin(), v.end(), [&](float& v){v /= norm;});
}

void Utility::l2_normalize(std::vector<float>& v){
	float norm = l2_norm(v);
	if(norm == 0.f){
		std::cerr << "0 norm" << std::endl;
		exit(1);
	}
	std::for_each(v.begin(), v.end(), [&](float& v){v /= norm;});
}

void Utility::normalize_image(cv::Mat& image, cv::Mat& output){
	double min_value;
	double max_value;
	cv::minMaxLoc(image, &min_value, &max_value);
	image.convertTo(output, CV_32FC1, 1.0 / max_value);
}

