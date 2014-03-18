#ifndef MEDIANFILTERALGORITHM_H
#define MEDIANFILTERALGORITHM_H

#include "KernelWalker.h"
#include <algorithm>

class MedianFilterAlgorithm : public KernelWalker {
public:
	MedianFilterAlgorithm(int size) : KernelWalker(size) { }

	virtual int KernelWalker::doAlgorithm() {
		int * dataPtr = kernel.getDataPtr();
		int kernelSize = kernel.getSize();

		std::sort(dataPtr, dataPtr + (kernelSize * kernelSize));

		int median = dataPtr[kernelSize * kernelSize / 2];

		return median;
	}
};

#endif