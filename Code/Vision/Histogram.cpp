#include "Histogram.h"

Histogram::Histogram(ColorChannel ch, int s) : channel(ch), size(s) {
	// Minimum size is 1.
	if (size < 1) {
		size = 256;
	}

	// Initialize histogram.
	histogram = new double[size];

	int imageSize = channel.getSize() * 3;
	unsigned char * imageDataPtr = channel.getDataPointer();

	// Initialize all values in the histogram to zero.
	for (int i = 0; i < size; i++) {
		histogram[i] = 0;
	}

	// Fill histogram with color values.
	for (int i = 0; i < imageSize; i += 3)
	{
		histogram[((imageDataPtr[i] * size) / 256)]++;
	}
}

Histogram::Histogram(Histogram & h): channel(h.channel) {
	*this = h;
}

Histogram & Histogram::operator=(const Histogram & h) {
	// Copy everything.
	size = h.size;
	channel = h.channel;
	histogram = new double[size];

	// Individually copy every value.
	for (int i = 0; i < size; i++) {
		histogram[i] = h.histogram[i];
	}

	return *this;
}

Histogram::~Histogram() {
	// Delete histogram data.
	delete[] histogram;
}

void Histogram::exportHistogramCSV(std::string filename) {
	// Open file.
	std::ofstream output(filename);

	if (output.is_open()) {
		// Write value seperator to the .csv file.
		output << "sep=,\n";

		// Write the index and the histogram value seperated by a comma to the file.
		for (int i = 0; i < size; i++) {
			output << i << ',' << histogram[i] << std::endl;
		}
		
		// Close the file.
		output.close();
	}
}

void Histogram::equalizeHistogram() {
	// Bron: http://www.songho.ca/dsp/histogram/histogram.html
	int imageSize = channel.getSize();

	// Scale.
	double scale = (double) size / imageSize;

	// Create the lookup table.
	int * lookupTable = new int[size];

	// Fill the lookup table.
	lookupTable[0] = histogram[0] * scale;
	int total = 0;
	for (int i = 1; i < size; i++) {
		total += histogram[i];
		lookupTable[i] = total * scale;
	}

	imageSize *= 3;
	unsigned char * imageDataPtr = channel.getDataPointer();

	// For every pixel in the image, find the new color value in the lookup table.
	for (int i = 0; i < imageSize; i += 3)
	{
		imageDataPtr[i] = lookupTable[imageDataPtr[i]];
	}
	
	// Delete the lookup table.
	delete[] lookupTable;
}