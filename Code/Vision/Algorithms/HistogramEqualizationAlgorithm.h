#ifndef HISTOGRAMEQUALIZATION_H
#define HISTOGRAMEQUALIZATION_H

#include "../Image.h"
#include "../Histogram.h"
#include "GrayscaleAlgorithm.h"

class HistogramEqualizationAlgorithm {
public:
	static void doAlgorithm(Image & image, bool grayScale = false) {
		if (grayScale) {
			GrayscaleAlgorithm::doAlgorithm(image);
		}

		Histogram redHistogram(image.getRedChannel());
		Histogram greenHistogram(image.getGreenChannel());
		Histogram blueHistogram(image.getBlueChannel());

		greenHistogram.equalizeHistogram();
		blueHistogram.equalizeHistogram();
		redHistogram.equalizeHistogram();

		if (grayScale) {
			int size = image.getWidth() * image.getHeight() * 3;
			unsigned char * ptr = image.getDataPointer();
			int red = 0;
			for (int x = 0; x < size; x += 3) {
				red = ptr[x];

				ptr[x + 1] = red;
				ptr[x + 2] = red;
			}
		}
	}
};

#endif