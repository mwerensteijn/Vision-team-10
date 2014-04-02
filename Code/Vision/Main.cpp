#include <iostream>
#include "FreeImage.h"
#include "Image.h"
#include "Histogram.h"
#include "Algorithms.h"

using namespace std;

int main(int argc, char ** argv) {
	Image::loadLibrary();

	Image image(argv[1]);
	Image auto_image(image);
	Image threshold(image);

	string name = argv[1];
	int clusters = std::atoi(argv[2]);

	std::cout << clusters << std::endl;

	if (image.isLoaded()) {
		//1
		KMeansClusteringAlgorithm::doAlgorithm(auto_image, clusters);
		auto_image.saveImage("kMeansAuto_" + name);
		//3
		ThresholdAlgorithm::doAlgorithm(threshold);
		threshold.saveImage("threshold_" + name);

	}
	Image::unloadLibrary();

	return 0;
}