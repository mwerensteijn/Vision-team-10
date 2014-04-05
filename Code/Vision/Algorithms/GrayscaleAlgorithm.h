#ifndef GRAYSCALEALGORITHM_H
#define GRAYSCALEALGORITHM_H

#include "../Image.h"

class GrayscaleAlgorithm {
public:
	static void doAlgorithm(Image & image) {
		int size = image.getWidth() * image.getHeight() * 3;

		unsigned char * ptr = image.getDataPointer();

		unsigned char red, green, blue;

		for (int x = 0; x < size; x += 3) {
			red = ptr[x];
			green = ptr[x + 1];
			blue = ptr[x + 2];

			// GrayScale calculation
			unsigned char grayscale = (unsigned char) ((red * .3) + (green * .59) + (blue * .11));

			ptr[x] = grayscale;
			ptr[x + 1] = grayscale;
			ptr[x + 2] = grayscale;
		}
	}
};

#endif