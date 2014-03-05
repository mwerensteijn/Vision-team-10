#include <iostream>
#include "Image.h"
#include "Histogram.h"
#include "Algorithms/InverseAlgorithm.h"
#include "Algorithms/GrayscaleAlgorithm.h"

using namespace std;

int main() {
	Image image("img.jpg");

	if (image.isLoaded()) {
		//InverseAlgorithm().doAlgorithm(image);
		GrayscaleAlgorithm().doAlgorithm(image);
		Histogram histogram(image);
		histogram.exportHistogramCSVRed("output.csv");

		image.saveImage("output.jpg");
	}


	return 0;
}