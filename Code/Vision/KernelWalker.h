#ifndef KERNELWALKER_H
#define KERNELWALKER_H

#include "Image.h"
#include "Kernel.h"

class KernelWalker {
public:
	KernelWalker(int size);
	KernelWalker(KernelWalker & kw);

	void runAlgorithm(Image & image);
	virtual int doAlgorithm() = 0;
protected:
	Kernel kernel;
	int size;
};

#endif