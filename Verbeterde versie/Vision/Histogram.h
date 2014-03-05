#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "Image.h"

class Histogram {
public:
	Histogram(Image & image, int s = 256);
	Histogram(Histogram & h);
	~Histogram();

	Histogram & operator=(const Histogram & h);

	void createHistogram(Image & image, double * data);
	void exportHistogramCSVRed(std::string filename);

private:
	int * red;
	int * green;
	int * blue;
	int size;
};

#endif