/*
 * FeatureDescriptor.cpp
 *
 *  Created on: Apr 3, 2013
 *      Author: zxwang
 */

#include "FeatureDescriptor.h"

FeatureDescriptor::FeatureDescriptor() {

}

FeatureDescriptor::~FeatureDescriptor() {

}

void FeatureDescriptor::set_descriptor(const std::vector<float>& descriptor){
	m_data.assign(descriptor.begin(), descriptor.end());
}

std::vector<float> FeatureDescriptor::get_descriptor(){
	return m_data;
}

std::ostream& operator<<(std::ostream& os, const FeatureDescriptor& descriptor){
	std::for_each(descriptor.m_data.begin(), descriptor.m_data.end(), [&](float v){os << v << "\t";});
	os << std::endl;
	return os;
}
