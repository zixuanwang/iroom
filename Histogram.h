/*
 * Histogram.h
 *
 *  Created on: Apr 3, 2013
 *      Author: zxwang
 */

#ifndef HISTOGRAM_H_
#define HISTOGRAM_H_
#include "FeatureDescriptor.h"

class Histogram : public FeatureDescriptor {
public:
	Histogram(float min, float max, float step); // constructor with min value, max value and step.
	Histogram(int num_bins); // constructor with number of bins.
	virtual ~Histogram();
	int get_num_bin(){return m_num_bins;}
	void add(float value, int frequency = 1); // add a new value to the histogram.
	void add(int index, int frequency = 1); // add a new value with the bin index.
protected:
	float m_min;
	float m_max;
	float m_step;
	int m_num_bins;
};

#endif /* HISTOGRAM_H_ */
