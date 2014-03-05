#ifndef MASKLOOPER_H
#define MASKLOOPER_H

#include "../Image.h"
#include <math.h>

class MaskLooper {
public:
	void loopMask(unsigned char * src, unsigned char * dst) {

	}

	int timesToLoop(int maskSize, int image_height, int image_width) {
		int borderPixels;
		if (maskSize % 2 == 1) { //uneven mask (has middle pixel)
			borderPixels = (maskSize - 1) / 2;
		}
		else if (maskSize % 2 == 0) { //even mask (doesnt have middle pixel)
			borderPixels = maskSize / 2;
		}
		int skipPixels;
		skipPixels = (image_height * borderPixels * 2) + (image_width * borderPixels * 2) - (4 * (pow(borderPixels, 2)));
		int amountOfTimes;
		amountOfTimes = (image_height * image_width) - skipPixels;

		for (int h = borderPixels; h < image_height - borderPixels; h++) {
			for (int w = borderPixels; w < image_width - borderPixels; w++) {

			}
		}

		return amountOfTimes;
	}
};

#endif