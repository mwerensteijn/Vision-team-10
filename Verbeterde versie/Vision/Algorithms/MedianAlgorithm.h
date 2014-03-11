#ifndef MEDIANALGORITHM_H
#define MEDIANALGORITHM_H

#include "VisionAlgorithm.h"
#include "MaskLooper.h"
#include <vector>
#include <algorithm>

#define MASKSIZE 3

class MedianAlgorithm : public VisionAlgorithm {
public:
	void VisionAlgorithm::doAlgorithm(Image & image) {
		MaskLooper p;

		Image source = image;

		int size = image.getWidth() * image.getHeight() * 3;
		int height = image.getHeight();
		int width = image.getWidth();
		int borderPixels = p.getBorderPixels(MASKSIZE);

		unsigned char * src = source.getDataPointer();
		unsigned char * dst = image.getDataPointer();

		memcpy(dst, src, size);
		int arrayR[MASKSIZE*MASKSIZE];
		int arrayG[MASKSIZE*MASKSIZE];
		int arrayB[MASKSIZE*MASKSIZE];
		int maskTotal = MASKSIZE*MASKSIZE;
		int counter = 0;
		for (int h = borderPixels; h < height - borderPixels; h++) {
			for (int w = borderPixels; w < width - borderPixels; w++) {
				for (int newW = w; newW < (w + 3); newW++)
				{
					for (int newH = h; newH < (h + 3); newH++)
					{
						arrayR[counter] = (int)src[3 * ((newH - 1) * width + (newW - 1))];
						arrayG[counter] = (int)src[3 * ((newH - 1) * width + (newW - 1)) + 1];
						arrayB[counter] = (int)src[3 * ((newH - 1) * width + (newW - 1)) + 2];
						counter++;
					}
				}
				dst[(3 * (h * width + w))] = (char)getMedian(arrayR, maskTotal);
				dst[(3 * (h * width + w)) + 1] = (char)getMedian(arrayG, maskTotal);
				dst[(3 * (h * width + w)) + 2] = (char)getMedian(arrayB, maskTotal);
				counter = 0;
			}
		}
	}

	double getMedian(int values[], int maskTotal) {
		double median;
		size_t size = maskTotal;
		std::sort(values, values + maskTotal);
		if (size % 2 == 0) {
			median = (values[size / 2 - 1] + values[size / 2]) / 2;
		}
		else {
			median = values[size / 2];
		}
		return median;
	}
};

#endif