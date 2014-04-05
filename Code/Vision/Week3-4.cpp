#include <iostream>
#include "FreeImage.h"
#include "Image.h"
#include "Histogram.h"
#include "Algorithms.h"

using namespace std;

int sss(int argc, char ** argv) {
	if (argc >= 2) {
		if (argc >= 3) {
			Image::loadLibrary();

			Image image(argv[1]);

			string name = argv[1];
			int clusters = std::atoi(argv[2]);

			if (image.isLoaded()) {
				// Opdracht 1
				Image auto_image(image);
				KMeansClusteringAlgorithm::doAlgorithm(auto_image, clusters);
				auto_image.saveImage("kMeansAuto_" + name);

				cout << "KMeans Clustered image saved: kMeansAuto_" << name.c_str() << ".bmp\n";


				// Opdracht 2
				Image threshold(image);
				ThresholdAlgorithm::doAlgorithm(threshold);
				threshold.saveImage("threshold_" + name);

				cout << "Thresholded image saved: threshold_" << name.c_str() << ".bmp\n";
			
				cout << "DONE\n";
			}
			else {
				cout << "Can't find the image.\n";
			}

			Image::unloadLibrary();
		}
		else {
			cout << "Please enter a cluster count.\n";
		}
	}
	else {
		cout << "Please enter a file name.\n";
	}

	cin.get();

	return 0;
}