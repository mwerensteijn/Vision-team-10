#ifndef KERNELWALKER_H
#define KERNELWALKER_H

#include "Image.h"
#include "Kernel.h"

class KernelWalker {
public:
	// Constructor(kernelsize);
	KernelWalker(int size);	

	// Run the algorithm on the image.
	void runAlgorithm(Image & image);
	// doAlgorithm must be overriden by classes that extend this class.
	virtual int doAlgorithm() = 0;
protected:
	// The kernel holds the color values that are loaded from the image.
	Kernel kernel;
	// KernelSize.
	int size;
};

#endif