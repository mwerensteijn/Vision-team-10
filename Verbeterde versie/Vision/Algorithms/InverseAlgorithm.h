#ifndef INVERSEALGORITHM_H
#define INVERSEALGORITHM_H

#include "VisionAlgorithm.h"

class InverseAlgorithm : public VisionAlgorithm {
public:
	void VisionAlgorithm::doAlgorithm(Image & image) {
		int size = image.getWidth() * image.getHeight() * 3;

		unsigned char * ptr = image.getDataPointer();

		for (int x = 0; x < size; x++) {
			ptr[x] = ~ptr[x];
		}
	}
};

#endif