#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "Image.h"

class Histogram {
public:
	// Constructors.
	Histogram(ColorChannel ch, int s = 256); // Constructor
	Histogram(Histogram & h);				 // Copy Constructor.
	~Histogram();							 // Deconstructor

	// Assignment operator.
	Histogram & operator=(const Histogram & h);

	// Equalize histogram.
	void equalizeHistogram();
	// Export Histogram to file.
	void exportHistogramCSV(std::string filename);
private:
	// Holds the colorchannel.
	ColorChannel channel;

	// Holds the histogram values.
	double * histogram;

	// Holds the image size.
	int size;
};

#endif