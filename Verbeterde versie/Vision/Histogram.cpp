#include "Histogram.h"

Histogram::Histogram(Image & image, int s) {
	size = s;

	red = new int[size];
	green = new int[size];
	blue = new int[size];

	for (int i = 0; i < size; i++) {
		red[i] = 0;
		green[i] = 0;
		blue[i] = 0;
	}

	unsigned char * imagePtr = image.getDataPointer();

	int size = image.getWidth() * image.getHeight();

	for (int i = 0; i < size; i += 3) {		
		red[imagePtr[0]]++;
		green[imagePtr[1]]++;
		blue[imagePtr[2]]++;

		imagePtr += 3;
	}
}

Histogram::~Histogram() {
	delete[] red;
	delete[] green;
	delete[] blue;
}


Histogram::Histogram(Histogram & h) {
	size = h.size;

	for (int i = 0; i < size; i++) {
		red[i] = h.red[i];
		green[i] = h.green[i];
		blue[i] = h.blue [i];
	}
}

Histogram & Histogram::operator=(const Histogram & h) {
	size = h.size;

	for (int i = 0; i < size; i++) {
		red[i] = h.red[i];
		green[i] = h.green[i];
		blue[i] = h.blue[i];
	}

	return *this;
}

void Histogram::exportHistogramCSVRed(std::string filename) {
	std::ofstream output(filename);

	if (output.is_open()) {
		for (int i = 0; i < size; i++) {
			output << i << ',' << red[i] << std::endl;
		}

		output.close();
	}

}