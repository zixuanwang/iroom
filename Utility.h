/*
 * Utility.h
 *
 *  Created on: Apr 3, 2013
 *      Author: zxwang
 */

#ifndef UTILITY_H_
#define UTILITY_H_
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <vector>

class Utility {
public:
	Utility();
	~Utility();
	static float l1_norm(const std::vector<float>& v);
	static float l2_norm(const std::vector<float>& v);
	static void l1_normalize(std::vector<float>& v);
	static void l2_normalize(std::vector<float>& v);
	static void normalize_image(cv::Mat& image, cv::Mat& output);
};

#endif /* UTILITY_H_ */
