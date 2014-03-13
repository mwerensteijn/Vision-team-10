#include <iostream>
#include "Image.h"
#include "Histogram.h"
#include "Algorithms/InverseAlgorithm.h"
#include "Algorithms/GrayscaleAlgorithm.h"
#include "Algorithms/SaltnPepperAlgorithm.h"
#include "Algorithms/MedianAlgorithm.h"
#include "Algorithms/MinimumAlgorithm.h"
#include "Algorithms/MaximumAlgorithm.h"

using namespace std;

int main(int argc, char ** argv) {
	Image image(argv[1]);
	string filename = argv[1];
	

	if (image.isLoaded()) {
		Image gray_image(image);
		Image noise_image(image);
		
		//InverseAlgorithm().doAlgorithm(image);
		GrayscaleAlgorithm().doAlgorithm(gray_image);
		SaltnPepperAlgorithm().doAlgorithm(noise_image);
		Image median_image(noise_image);
		Image minimum_image(noise_image);
		Image maximum_image(noise_image);
		MinimumAlgorithm().doAlgorithm(minimum_image);
		MedianAlgorithm().doAlgorithm(median_image);
		MaximumAlgorithm().doAlgorithm(maximum_image);
		
		Histogram histogram(image);
		histogram.exportHistogramCSVRed("output.csv");

		gray_image.saveImage("grey_" + filename);
		noise_image.saveImage("noise_" + filename);
		median_image.saveImage("median_" + filename);
		minimum_image.saveImage("min_" + filename);
		maximum_image.saveImage("max_" + filename);
	}
	else {
		cout << "File is invalid or does not exist" << endl;
	}

	return 0;
}