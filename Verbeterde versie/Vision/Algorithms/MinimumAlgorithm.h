#ifndef MINIMUMALGORITHM_H
#define MINIMUMALGORITHM_H

#include "VisionAlgorithm.h"
#include "MaskLooper.h"
#include <vector>
#include <algorithm>

#define MASKSIZE 3

class MinimumAlgorithm : public VisionAlgorithm {
public:
	void VisionAlgorithm::doAlgorithm(Image & image) {
		int maskSize = MASKSIZE;

		MaskLooper p;

		int size = image.getWidth() * image.getHeight() * 3;
		int height = image.getHeight();
		int width = image.getWidth();
		int borderPixels = p.getBorderPixels(maskSize);

		unsigned char * dst = image.getDataPointer();
		std::vector<int> src;
		src.resize(size);
		for (int i = 0; i < size; i++) {
			src[i] = dst[i];
		}

		int* arrayR = new int[maskSize*maskSize];
		int* arrayG = new int[maskSize*maskSize];
		int* arrayB = new int[maskSize*maskSize];
		int maskTotal = maskSize*maskSize;
		int counter = 0;
		for (int h = borderPixels; h < height - borderPixels; h++) {
			for (int w = borderPixels; w < width - borderPixels; w++) {
				for (int newW = w; newW < (w + maskSize); newW++)
				{
					for (int newH = h; newH < (h + maskSize); newH++)
					{
						arrayR[counter] = (int)src[3 * ((newH - borderPixels) * width + (newW - borderPixels))];
						arrayG[counter] = (int)src[3 * ((newH - borderPixels) * width + (newW - borderPixels)) + 1];
						arrayB[counter] = (int)src[3 * ((newH - borderPixels) * width + (newW - borderPixels)) + 2];
						counter++;
					}
				}
				dst[(3 * (h * width + w))] = (char)getMinimum(arrayR, maskTotal);
				dst[(3 * (h * width + w)) + 1] = (char)getMinimum(arrayG, maskTotal);
				dst[(3 * (h * width + w)) + 2] = (char)getMinimum(arrayB, maskTotal);
				counter = 0;
			}
		}
		delete[] arrayR;
		delete[] arrayG;
		delete[] arrayB;
	}

	int getMinimum(int values[], int maskTotal) {
		int minimum = values[0];
		for (int counter = 0; counter < maskTotal; counter++) {
			if (minimum > values[counter]) {
				minimum = values[counter];
			}
		}
		return minimum;
	}
};

#endif