#ifndef __VISIONALGORITHM_H__
#define __VISIONALGORITHM_H__

#include "../Image.h"

class VisionAlgorithm {
public:
	virtual void doAlgorithm(Image &image) = 0;
};

#endif