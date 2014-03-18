#include "Histogram.h"

Histogram::Histogram(ColorChannel ch, int s) : channel(ch), size(s) {
	if (size < 0) {
		size = 256;
	}

	histogram = new double[size];

	int imageSize = channel.getSize() * 3;
	unsigned char * imageDataPtr = channel.getDataPointer();

	for (int i = 0; i < size; i++) {
		histogram[i] = 0;
	}

	for (int i = 0; i < imageSize; i += 3)
	{
		histogram[((imageDataPtr[i] * size) / 256)]++;
	}
}

Histogram::Histogram(Histogram & h): channel(h.channel) {
	*this = h;
}

Histogram & Histogram::operator=(const Histogram & h) {
	size = h.size;
	channel = h.channel;
	histogram = new double[size];

	for (int i = 0; i < size; i++) {
		histogram[i] = h.histogram[i];
	}

	return *this;
}

Histogram::~Histogram() {
	delete[] histogram;
}

void Histogram::exportHistogramCSV(std::string filename) {
	std::ofstream output(filename);

	if (output.is_open()) {
		output << "sep=,\n";

		for (int i = 0; i < size; i++) {
			output << i << ',' << histogram[i] << std::endl;
		}

		output.close();
	}
}

void Histogram::equalizeHistogram() {
	// Bron: http://www.songho.ca/dsp/histogram/histogram.html
	int imageSize = channel.getSize();

	double scale = (double) size / imageSize;

	int * lookupTable = new int[size];

	lookupTable[0] = histogram[0] * scale;

	int totaal = 0;
	for (int i = 1; i < size; i++) {
		totaal += histogram[i];
		lookupTable[i] = totaal * scale;
	}

	imageSize *= 3;
	unsigned char * imageDataPtr = channel.getDataPointer();

	for (int i = 0; i < imageSize; i += 3)
	{
		imageDataPtr[i] = lookupTable[imageDataPtr[i]];
	}
	
	delete[] lookupTable;
}