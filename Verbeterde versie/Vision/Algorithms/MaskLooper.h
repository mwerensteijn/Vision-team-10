#ifndef MASKLOOPER_H
#define MASKLOOPER_H
#define RED 1
#define GREEN 2
#define BLUE 3

#include "../Image.h"
#include <math.h>
#include <vector>

using namespace std;

class MaskLooper {
public:
	int getBorderPixels(const int &maskSize) {
		int borderPixels = 0;
		if (maskSize % 2 == 1) { //uneven mask (has middle pixel)
			borderPixels = (maskSize - 1) / 2;
		}
		else if (maskSize % 2 == 0) { //even mask (doesnt have middle pixel)
			borderPixels = maskSize / 2;
		}
		return borderPixels;
	}
};

#endif