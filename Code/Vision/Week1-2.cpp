#include <iostream>
#include "FreeImage.h"
#include "Image.h"
#include "Histogram.h"
#include "Algorithms.h"

using namespace std;

int week1(int argc, char ** argv) {
	Image::loadLibrary();

	Image image(argv[1]);
	string name = argv[1];

	Image grey_image(image);
	Image bin_image(image);

	Image noise_image(image);

	if (image.isLoaded()) {
		//Opdracht 1
		//1
		GrayscaleAlgorithm::doAlgorithm(grey_image);
		grey_image.saveImage("grey_" + name);
		//2
		Histogram normalizedHistogram256 = Histogram(grey_image.getRedChannel());
		Histogram normalizedHistogram10 = Histogram(grey_image.getRedChannel(), 10);
		normalizedHistogram256.exportHistogramCSV("Hist256.csv");
		normalizedHistogram10.exportHistogramCSV("Hist10.csv");
		//3
		HistogramEqualizationAlgorithm::doAlgorithm(image, true);
		//4
		//MITCHELL VANAVOND
		//5
		Histogram redHistogram = Histogram(bin_image.getRedChannel(), 10);
		Histogram greenHistogram = Histogram(bin_image.getGreenChannel(), 10);
		Histogram blueHistogram = Histogram(bin_image.getBlueChannel(), 10);
		redHistogram.exportHistogramCSV("RedHist.csv");
		greenHistogram.exportHistogramCSV("GreenHist.csv");
		blueHistogram.exportHistogramCSV("BlueHist.csv");

		//Opdracht 2
		//6a
		SaltnPepperAlgorithm::doAlgorithm(noise_image);
		noise_image.saveImage("noise_" + name);
		Image mda_image(noise_image);
		Image min_image(noise_image);
		Image max_image(noise_image);
		//6b
		MedianFilterAlgorithm mda = MedianFilterAlgorithm(3);
		mda.runAlgorithm(mda_image);
		mda_image.saveImage("median_" + name);
		//7a
		MinimumFilterAlgorithm min = MinimumFilterAlgorithm(3);
		min.runAlgorithm(min_image);
		min_image.saveImage("min_" + name);
		//7b
		MaximumFilterAlgorithm max = MaximumFilterAlgorithm(3);
		max.runAlgorithm(max_image);
		max_image.saveImage("max_" + name);
	}
	Image::unloadLibrary();

	return 0;
}