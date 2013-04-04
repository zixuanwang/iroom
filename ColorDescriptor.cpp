/*
 * ColorDescriptor.cpp
 *
 *  Created on: Apr 3, 2013
 *      Author: zxwang
 */

#include "ColorDescriptor.h"

ColorDescriptor::ColorDescriptor(int channel_num_bins) : m_channel_num_bins(channel_num_bins) {

}

ColorDescriptor::~ColorDescriptor() {

}

void ColorDescriptor::compute(cv::Mat& image, cv::Mat& mask){
	int histSize[] = { m_channel_num_bins, m_channel_num_bins, m_channel_num_bins };
	float hranges[] = { 0.0, 255.0 };
	const float* ranges[] = { hranges, hranges, hranges };
	int channels[] = { 0, 1, 2 };
	cv::MatND hist;
	cv::calcHist(&image, 1, channels, mask, hist, 3, histSize, ranges);
	m_data.reserve(m_channel_num_bins * m_channel_num_bins * m_channel_num_bins);
	for (int i = 0; i < m_channel_num_bins; ++i) {
		for (int j = 0; j < m_channel_num_bins; ++j) {
			for (int k = 0; k < m_channel_num_bins; ++k) {
				float value = hist.at<float>(i, j, k);
				m_data.push_back(value);
			}
		}
	}
	Utility::l2_normalize(m_data);
}

void ColorDescriptor::update_background(cv::Mat& image, cv::Mat& mask){
	m_bg_model(image, mask);
}
