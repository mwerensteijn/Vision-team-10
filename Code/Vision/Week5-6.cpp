#include <iostream>
#include "FreeImage.h"
#include "Image.h"
#include "Histogram.h"
#include "Algorithms.h"

using namespace std;

int main(int argc, char ** argv) {
	if (argc >= 2) {
		if (argc >= 3) {
			if (argc >= 4) {
				Image::loadLibrary();

				Image image(argv[1]);
				string name = argv[1];

				if (image.isLoaded()) {
					TransformMatrix::doAlgorithm(image, std::atoi(argv[3]), argv[2]);
					image.saveImage("transformed_" + name);
					
					cout << "Transformed image saved: " << name.c_str() << ".bmp\n";

					cout << "DONE\n";
				}
				else {
					cout << "Can't find the image.\n";
				}

				Image::unloadLibrary();
			}
			else {
				cout << "Please enter an interpolation order(0, or 1).\n";
			}
		}
		else {
			cout << "Please enter a matrix filename.\n";
		}
	}
	else {
		cout << "Please enter a file name.\n";
	}

	cin.get();

	return 0;
}