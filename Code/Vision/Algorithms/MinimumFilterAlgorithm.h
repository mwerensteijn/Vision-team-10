#ifndef MINIMUMFILTERALGORITHM_H
#define MINIMUMFILTERALGORITHM_H

#include "KernelWalker.h"
#include <algorithm>

class MinimumFilterAlgorithm : public KernelWalker {
public:
	MinimumFilterAlgorithm(int size) : KernelWalker(size) { }

	virtual int KernelWalker::doAlgorithm() {
		int * dataPtr = kernel.getDataPtr();
		int kernelSize = kernel.getSize() * kernel.getSize();

		int minimum = dataPtr[0];

		for (int i = 0; i < kernelSize; i++) {
			if (minimum > dataPtr[i]) {
				minimum = dataPtr[i];
			}
		}
		
		return minimum;
	}
};

#endif