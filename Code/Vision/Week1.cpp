#include <iostream>
#include "FreeImage.h"
#include "Image.h"
#include "Histogram.h"
#include "Algorithms.h"

using namespace std;

int bla(int argc, char ** argv) {
	if (argc >= 2) {
		Image::loadLibrary();

		Image image(argv[1]);
		string name = argv[1];

		if (image.isLoaded()) {
			// Opdracht 1
			Image grey_image(image);
			GrayscaleAlgorithm::doAlgorithm(grey_image);
			grey_image.saveImage("grey_" + name);

			cout << "Gray image saved: grey_" << name.c_str() << ".bmp\n";

			// Opdracht 2
			Histogram normalizedHistogram256 = Histogram(grey_image.getRedChannel());
			Histogram normalizedHistogram10 = Histogram(grey_image.getRedChannel(), 10);

			normalizedHistogram256.exportHistogramCSV("Hist256.csv");
			normalizedHistogram10.exportHistogramCSV("Hist10.csv");

			cout << "Histograms created: Hist256.csv and Hist10.csv" << std::endl;
			
			// Opdracht 3
			HistogramEqualizationAlgorithm::doAlgorithm(image, true);
			image.saveImage("equalized");

			cout << "Equalized image, saved: equalized.bmp\n";
		
			// Opdracht 4
			image.saveImageRed(string("R_") + name);
			image.saveImageGreen(string("G_") + name);
			image.saveImageBlue(string("B_") + name);
			cout << "Individual color channels saved: R_" << name.c_str() << ".bmp, G_" << name.c_str() << ".bmp, B_" << name.c_str() << ".bmp\n";

			// Opdracht 5
			Image bin_image(image);
			Histogram redHistogram = Histogram(bin_image.getRedChannel(), 10);
			Histogram greenHistogram = Histogram(bin_image.getGreenChannel(), 10);
			Histogram blueHistogram = Histogram(bin_image.getBlueChannel(), 10);

			redHistogram.exportHistogramCSV("RedHist.csv");
			greenHistogram.exportHistogramCSV("GreenHist.csv");
			blueHistogram.exportHistogramCSV("BlueHist.csv");

			cout << "Histograms created: RedHist.csv, GreenHist.csv and BlueHist.csv\n" << std::endl;

			cout << "DONE\n";
		}
		else {
			cout << "Can't find the image.\n";
		}

		Image::unloadLibrary();
	} else {
		cout << "Please enter a file name.\n";
	}

	cin.get();

	return 0;
}