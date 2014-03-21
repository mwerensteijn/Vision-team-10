#ifndef MEDIANDIFFERENCEALGORITHM_H
#define MEDIANDIFFERENCEALGORITHM_H

#include "../Image.h"
#include "../Algorithms.h"

#include <math.h>

class MedianDifferenceAlgorithm {
public:
	/*static void doAlgorithm(Image & image) {
		int imageSize = image.getWidth() * image.getHeight() * 3;
		unsigned char * destDataPtr = image.getDataPointer();

		int DIFFERENCE = 5;

		for (int i = 0; i < imageSize; i += 3) {
			float rDest = destDataPtr[i];
			float gDest = destDataPtr[i + 1];
			float bDest = destDataPtr[i + 2];

			std::cout << "r: " << rDest << "\tg: " << gDest << "\tb: " << bDest << "\n";

			float hDest;
			float sDest;
			float vDest;

			RGB2HSV(rDest, gDest, bDest, hDest, sDest, vDest);

			std::cout << "HSV: " << hDest << " " << sDest << " " << vDest << std::endl;
			std::cin.get();
		}
	}
	*/
	static void doAlgorithm(Image & image) {
		Image median("median_image.jpg");

		//MedianFilterAlgorithm mf(11);
		//mf.runAlgorithm(image);

		if (median.isLoaded()) {
			int imageSize = image.getWidth() * image.getHeight() * 3;
			unsigned char * medDataPtr = median.getDataPointer();
			unsigned char * destDataPtr = image.getDataPointer();

			int DIFFERENCE = 5;

			for (int i = 0; i < imageSize; i += 3) {
				float rMed = medDataPtr[i];
				float gMed = medDataPtr[i + 1];
				float bMed = medDataPtr[i + 2];

				float hMed;
				float sMed;
				float vMed;

				RGB2HSV(rMed, gMed, bMed, hMed, sMed, vMed);

				float rDest = destDataPtr[i];
				float gDest = destDataPtr[i + 1];
				float bDest = destDataPtr[i + 2];

				float hDest;
				float sDest;
				float vDest;

				RGB2HSV(rDest, gDest, bDest, hDest, sDest, vDest);

				if (hMed >= 30 && hMed <= 60) {
					destDataPtr[i] = 255;
					destDataPtr[i + 1] = 255;
					destDataPtr[i + 2] = 255;
				}
				else {
					destDataPtr[i] = 0;
					destDataPtr[i + 1] = 0;
					destDataPtr[i + 2] = 0;
				}

				/*std::cout << "Difference: " << difference << std::endl;
				std::cout << "HSV: " << hDest << " " << sDest << " " << vDest << std::endl;
				std::cin.get();*/
			}
		}
	}

	static void RGB2HSV(float r, float g, float b, float & h, float & s, float & v)
	{
		double      min, max, delta;

		min = r < g ? r : g;
		min = min  < b ? min : b;

		max = r > g ? r : g;
		max = max  > b ? max : b;

		v = max;                                // v
		delta = max - min;
		if (max > 0.0) {
			s = (delta / max);                  // s
		}
		else {
			// r = g = b = 0                        // s = 0, v is undefined
			s = 0.0;
			h = NAN;                            // its now undefined
			return ;
		}
		if (r >= max)                           // > is bogus, just keeps compilor happy
			h = (g - b) / delta;        // between yellow & magenta
		else
		if (g >= max)
			h = 2.0 + (b - r) / delta;  // between cyan & yellow
		else
			h = 4.0 + (r - g) / delta;  // between magenta & cyan

		h *= 60.0;                              // degrees

		if (h < 0.0)
			h += 360.0;
	}

	/*static void doAlgorithm(Image & image) {
		Image median("median_image.jpg");

		//MedianFilterAlgorithm mf(11);
		//mf.runAlgorithm(image);

		int imageSize = image.getWidth() * image.getHeight() * 3;
		unsigned char * medDataPtr = median.getDataPointer();
		unsigned char * destDataPtr = image.getDataPointer();

		int DIFFERENCE = 10;

		for (int i = 0; i < imageSize; i += 3) {
			if ((abs(medDataPtr[i] - destDataPtr[i]) < DIFFERENCE) &&
				(abs(medDataPtr[i + 1] - destDataPtr[i + 1]) < DIFFERENCE) &&
				(abs(medDataPtr[i + 2] - destDataPtr[i + 2])) < DIFFERENCE) {
				destDataPtr[i] = 255;
				destDataPtr[i + 1] = 255;
				destDataPtr[i + 2] = 255;
			}
			else {
				destDataPtr[i] = 0;
				destDataPtr[i + 1] = 0;
				destDataPtr[i + 2] = 0;
			}
		}
	}*/
};

#endif