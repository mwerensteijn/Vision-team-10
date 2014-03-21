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
		/*SaltnPepperAlgorithm::doAlgorithm(image);
		image.saveImage("noised_image.jpg");

		Image median(image);
		MedianFilterAlgorithm mf(3);
		mf.runAlgorithm(median);
		median.saveImage("median_image.jpg");

		Image minimum(image);
		MinimumFilterAlgorithm mfa(3);
		mfa.runAlgorithm(minimum);
		minimum.saveImage("minimum.jpg");

		Image maximum(image);
		MaximumFilterAlgorithm mfb(3);
		mfb.runAlgorithm(maximum);
		maximum.saveImage("maximum.jpg");*/

		MedianDifferenceAlgorithm::doAlgorithm(image);
		image.saveImage("HUH.jpg");
	}

	Image::unloadLibrary();

	return 0;
}