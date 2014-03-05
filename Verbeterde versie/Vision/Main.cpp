#include <iostream>
#include "Image.h"
#include "Histogram.h"
#include "Algorithms/InverseAlgorithm.h"
#include "Algorithms/GrayscaleAlgorithm.h"
#include "Algorithms/SaltnPepperAlgorithm.h"

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
		Histogram histogram(image);
		histogram.exportHistogramCSVRed("output.csv");

		gray_image.saveImage("grey_" + filename);
		noise_image.saveImage("noise_" + filename);
	}
	else {
		cout << "File is invalid or does not exist" << endl;
	}

	return 0;
}