/*
 * FeatureDescriptor.h
 *
 *  Created on: Apr 3, 2013
 *      Author: zxwang
 */

#ifndef FEATUREDESCRIPTOR_H_
#define FEATUREDESCRIPTOR_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Utility.h"

class FeatureDescriptor {
public:
	FeatureDescriptor();
	virtual ~FeatureDescriptor();
	void set_descriptor(const std::vector<float>& descriptor);
	std::vector<float> get_descriptor();
	// overload the output function.
	friend std::ostream& operator<<(std::ostream& os, const FeatureDescriptor& descriptor);
protected:
	std::vector<float> m_data;
};





#endif /* FEATUREDESCRIPTOR_H_ */
