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
		KMeansClusteringAlgorithm::doAlgorithm(image, 3);
		image.saveImage("CLUSTERED.jpg");
	}

	Image::unloadLibrary();

	return 0;
}