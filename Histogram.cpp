/*
 * Histogram.cpp
 *
 *  Created on: Apr 3, 2013
 *      Author: zxwang
 */

#include "Histogram.h"

Histogram::Histogram(float min, float max, float step) : m_min(min), m_max(max), m_step(step) {
	m_num_bins = static_cast<int>((m_max - m_min) / m_step) + 1;
	if(m_num_bins < 0){
		std::cerr << "error in histogram size" << std::endl;
		exit(1);
	}
	m_data.assign(m_num_bins, 0.f);
}

Histogram::Histogram(int num_bins) : m_min(0.f), m_max(0.f), m_step(0.f), m_num_bins(num_bins){

}

Histogram::~Histogram() {

}

void Histogram::add(float value, int frequency){
	int index = static_cast<int>((value - m_min) / m_step);
	m_data[index] += frequency;
}

void Histogram::add(int index, int frequency){
	m_data[index] += frequency;
}
