#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "Image.h"

class Histogram {
public:
	Histogram(ColorChannel ch, int s = 256);
	Histogram(Histogram & h);
	~Histogram();

	Histogram & operator=(const Histogram & h);

	void equalizeHistogram();
	void exportHistogramCSV(std::string filename);
private:
	ColorChannel channel;
	double * histogram;
	int size;
};

#endif