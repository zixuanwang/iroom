/*
 * MotionDescriptor.h
 *
 *  Created on: Apr 3, 2013
 *      Author: zxwang
 */

#ifndef MOTIONDESCRIPTOR_H_
#define MOTIONDESCRIPTOR_H_
#include "FeatureDescriptor.h"

class MotionDescriptor : public FeatureDescriptor {
public:
	MotionDescriptor();
	virtual ~MotionDescriptor();
	void draw_optical_flow(const cv::Mat& flow, cv::Mat& cflow_map, int step);
	void compute(const cv::Mat& image, cv::Mat& flow);
private:
	cv::Mat m_prev;
};

#endif /* MOTIONDESCRIPTOR_H_ */
