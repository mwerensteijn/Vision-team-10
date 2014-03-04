#include <iostream>
#include "Image.h"
#include "Algorithms/InverseAlgorithm.h"

using namespace std;

int main() {
	Image image("img.jpg");

	if (image.isLoaded()) {
		InverseAlgorithm().doAlgorithm(image);
		image.saveImage("output.jpg");
	}


	return 0;
}