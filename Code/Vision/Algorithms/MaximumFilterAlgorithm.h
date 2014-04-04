#ifndef MAXIMUMFILTERALGORITHM_H
#define MAXIMUMFILTERALGORITHM_H

#include "KernelWalker.h"
#include <algorithm>

class MaximumFilterAlgorithm : public KernelWalker {
public:
	MaximumFilterAlgorithm(int size) : KernelWalker(size) { }

	virtual int KernelWalker::doAlgorithm() {
		int * dataPtr = kernel.getDataPtr();
		int kernelSize = kernel.getSize() * kernel.getSize();

		int maximum = dataPtr[0];

		for (int i = 0; i < kernelSize; i++) {
			if (maximum < dataPtr[i]) {
				maximum = dataPtr[i];
			}
		}

		return maximum;
	}
};

#endif