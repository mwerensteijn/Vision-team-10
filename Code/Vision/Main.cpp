#include <iostream>
#include "FreeImage.h"
#include "Image.h"
#include "Histogram.h"
#include "Algorithms.h"

using namespace std;

int main() {
	Image::loadLibrary();

	Image image("lenna.png");

	if (image.isLoaded()) {
		GrayscaleAlgorithm::doAlgorithm(image);
		ThresholdAlgorithm::doAlgorithm(image);
		image.saveImage("THRESHOLDED.jpg");
	}

	Image::unloadLibrary();

	return 0;
}