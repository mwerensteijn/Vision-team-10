#ifndef INVERSEALGORITHM_H
#define INVERSEALGORITHM_H

#include "../Image.h"

class InverseAlgorithm {
public:
	static void doAlgorithm(Image & image) {
		int size = image.getWidth() * image.getHeight() * 3;

		unsigned char * ptr = image.getDataPointer();

		for (int x = 0; x < size; x++) {
			ptr[x] = ~ptr[x];
		}
	}
};

#endif