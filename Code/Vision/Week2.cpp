#include <iostream>
#include "FreeImage.h"
#include "Image.h"
#include "Histogram.h"
#include "Algorithms.h"

using namespace std;

int sfd(int argc, char ** argv) {
	if (argc >= 2) {
		Image::loadLibrary();

		Image image(argv[1]);
		string name = argv[1];

		if (image.isLoaded()) {
			Image noise_image(image);

			// Opdracht 6a
			SaltnPepperAlgorithm::doAlgorithm(noise_image);
			noise_image.saveImage("noise_" + name);

			cout << "Noise image saved: noise_" << name.c_str() << ".bmp\n";

			// Opdracht 6b
			Image mda_image(noise_image);
			MedianFilterAlgorithm mda = MedianFilterAlgorithm(3);
			mda.runAlgorithm(mda_image);
			mda_image.saveImage("median_" + name);

			cout << "Median image created: median_" << name.c_str() << ".bmp\n";

			// Opdracht 7a
			Image min_image(noise_image);
			MinimumFilterAlgorithm min = MinimumFilterAlgorithm(3);
			min.runAlgorithm(min_image);
			min_image.saveImage("min_" + name);

			cout << "Min image created: min_" << name.c_str() << ".bmp\n";

			// Opdracht 7b
			Image max_image(noise_image);

			MaximumFilterAlgorithm max = MaximumFilterAlgorithm(3);
			max.runAlgorithm(max_image);
			max_image.saveImage("max_" + name);

			cout << "Max image created: max_" << name.c_str() << ".bmp\n";
			
			cout << "DONE\n";
		}
		else {
			cout << "Can't find the image.\n";
		}

		Image::unloadLibrary();
	}
	else {
		cout << "Please enter a file name.\n";
	}

	return 0;
}