/*
 * HoGDescriptor.h
 *
 *  Created on: Apr 3, 2013
 *      Author: zxwang
 */

#ifndef HOGDESCRIPTOR_H_
#define HOGDESCRIPTOR_H_

#include "FeatureDescriptor.h"

#define PI 3.1415926

class HoGDescriptor : public FeatureDescriptor {
public:
	HoGDescriptor(int num_bins = 9);
	virtual ~HoGDescriptor();
	void compute(cv::Mat& image, cv::Mat& mask);
	void compute_gradient(cv::Mat& image, std::vector<float>& histogram);
private:
	int m_num_bins;
	cv::HOGDescriptor m_hog;
	cv::Mat m_magnitude; // save the magnitude of the gradient.
	cv::Mat m_angle; // save the angle of the gradient.
};

#endif /* HOGDESCRIPTOR_H_ */
