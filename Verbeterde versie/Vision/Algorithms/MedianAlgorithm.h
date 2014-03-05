#ifndef MEDIANALGORITHM_H
#define MEDIANALGORITHM_H

#include "VisionAlgorithm.h"
#include "MaskLooper.h"

class MedianAlgorithm : public VisionAlgorithm {
public:
	void VisionAlgorithm::doAlgorithm(Image & image) {
		int size = image.getWidth() * image.getHeight() * 3;

		unsigned char * ptr = image.getDataPointer();
		unsigned char * cpy;

		memcpy(cpy, ptr, size);
		


	}
};

#endif