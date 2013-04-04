/*
 * ColorDescriptor.h
 *
 *  Created on: Apr 3, 2013
 *      Author: zxwang
 */

#ifndef COLORDESCRIPTOR_H_
#define COLORDESCRIPTOR_H_
#include "FeatureDescriptor.h"

class ColorDescriptor : public FeatureDescriptor{
public:
	ColorDescriptor(int channel_num_bins = 8);
	virtual ~ColorDescriptor();
	void compute(cv::Mat& image, cv::Mat& mask);
	void update_background(cv::Mat& image, cv::Mat& mask);
	void get_background(cv::Mat& background){m_bg_model.getBackgroundImage(background);}
private:
	int m_channel_num_bins;
	cv::Mat m_background;
	cv::BackgroundSubtractorMOG2 m_bg_model;
};

#endif /* COLORDESCRIPTOR_H_ */
