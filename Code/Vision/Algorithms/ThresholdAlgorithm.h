#ifndef THRESHOLDALGORITHM_H
#define THRESHOLDALGORITHM_H

#include "../Image.h"
#include <vector>

class ThresholdAlgorithm {
public:
	static void doAlgorithm(Image & image) {
		int srcHeight = image.getHeight();
		int srcWidth = image.getWidth();
		int amountData = srcHeight * srcWidth * 3;
		int size = srcHeight * srcWidth;

		unsigned char * dataptr = image.getDataPointer();

		//put values in array
		std::vector<int> values;
		for (int i = 0; i < amountData; i += 3) {
			values.push_back(dataptr[i]);
		}
		
		std::sort(values.begin() , values.end());
		int threshold = values[size / 2];
		std::cout << "Calculated threshold: " << threshold << std::endl;

		//Apply threshold to pixels
		int value = 0;
		for (int counter = 0; counter < amountData; counter += 3) {
			value = dataptr[counter];
			if (value <= threshold) {
				dataptr[counter] = 0;
				dataptr[counter + 1] = 0;
				dataptr[counter + 2] = 0;
			}
			else {
				dataptr[counter] = 255;
				dataptr[counter + 1] = 255;
				dataptr[counter + 2] = 255;
			}
		}
		

	}
};

#endif