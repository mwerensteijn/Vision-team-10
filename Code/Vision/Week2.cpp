#include <iostream>
#include "FreeImage.h"
#include "Image.h"
#include "Histogram.h"
#include "Algorithms.h"

using namespace std;

int s(int argc, char ** argv) {
	if (argc >= 2) {
		Image::loadLibrary();

		Image image(argv[1]);
		string name = argv[1];

		if (image.isLoaded()) {
			Image noise_image(image);

			// Opdracht 2 - 6a
			SaltnPepperAlgorithm::doAlgorithm(noise_image);
			noise_image.saveImage("noise_" + name);
			Image mda_image(noise_image);
			Image min_image(noise_image);
			Image max_image(noise_image);

			// Opdracht 2 - 6b
			MedianFilterAlgorithm mda = MedianFilterAlgorithm(3);
			mda.runAlgorithm(mda_image);
			mda_image.saveImage("median_" + name);
			cout << "Median image created: median_" << name.c_str() << std::endl;

			// Opdracht 2 - 7a
			MinimumFilterAlgorithm min = MinimumFilterAlgorithm(3);
			min.runAlgorithm(min_image);
			min_image.saveImage("min_" + name);
			cout << "Min image created: min_" << name.c_str() << std::endl;

			// Opdracht 2 - 7b
			MaximumFilterAlgorithm max = MaximumFilterAlgorithm(3);
			max.runAlgorithm(max_image);
			max_image.saveImage("max_" + name);
			cout << "Max image created: max_" << name.c_str() << std::endl;

			cin.get();
		}

		Image::unloadLibrary();
	}
	else {
		cout << "Please enter a file name.\n";
	}

	return 0;
}