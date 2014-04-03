#include <iostream>
#include "FreeImage.h"
#include "Image.h"
#include "Histogram.h"
#include "Algorithms.h"

using namespace std;

int main(int argc, char ** argv) {
	Image::loadLibrary();

	//1a
	Image image(argv[1]);
	string imageName = argv[1];

	//1b
	string fileName = argv[2];

	//1c
	int order = std::atoi(argv[3]);

	if (image.isLoaded()) {
		//1d

		//2a

		//2b

		//2c

		//3

	}
	Image::unloadLibrary();

	return 0;
}