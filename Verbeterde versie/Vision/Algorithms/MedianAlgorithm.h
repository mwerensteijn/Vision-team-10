#ifndef MEDIANALGORITHM_H
#define MEDIANALGORITHM_H

#define SWAP(a,b) temp=(a);(a)=(b);(b)=temp;

#include "VisionAlgorithm.h"
#include "MaskLooper.h"
#include <vector>
#include <algorithm>

#define MASKSIZE 3

class MedianAlgorithm : public VisionAlgorithm {
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
				dst[(3 * (h * width + w))] = (char)getMedian(arrayR, maskTotal);
				dst[(3 * (h * width + w)) + 1] = (char)getMedian(arrayG, maskTotal);
				dst[(3 * (h * width + w)) + 2] = (char)getMedian(arrayB, maskTotal);
				counter = 0;
			}
		}
		delete[] arrayR;
		delete[] arrayG;
		delete[] arrayB;
		
	}

	double getMedian(int values[], int maskTotal) {
		double median;
		/*size_t size = maskTotal;
		std::sort(values, values + maskTotal);
		if (size % 2 == 0) {
			median = (values[size / 2 - 1] + values[size / 2]) / 2;
		}
		else {
			median = values[size / 2];
		}*/

		median = quickselect(values, maskTotal, maskTotal / 2);

		return median;
	}

	int quickselect(int *arr, int n, int k) {
		unsigned long i, ir, j, l, mid;
		int a, temp;

		l = 0;
		ir = n - 1;
		for (;;) {
			if (ir <= l + 1) {
				if (ir == l + 1 && arr[ir] < arr[l]) {
					SWAP(arr[l], arr[ir]);
				}
				return arr[k];
			}
			else {
				mid = (l + ir) >> 1;
				SWAP(arr[mid], arr[l + 1]);
				if (arr[l] > arr[ir]) {
					SWAP(arr[l], arr[ir]);
				}
				if (arr[l + 1] > arr[ir]) {
					SWAP(arr[l + 1], arr[ir]);
				}
				if (arr[l] > arr[l + 1]) {
					SWAP(arr[l], arr[l + 1]);
				}
				i = l + 1;
				j = ir;
				a = arr[l + 1];
				for (;;) {
					do i++; while (arr[i] < a);
					do j--; while (arr[j] > a);
					if (j < i) break;
					SWAP(arr[i], arr[j]);
				}
				arr[l + 1] = arr[j];
				arr[j] = a;
				if (j >= k) ir = j - 1;
				if (j <= k) l = i;
			}
		}
	}
};

#endif