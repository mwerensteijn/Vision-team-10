#include "KernelWalker.h"

KernelWalker::KernelWalker(int s): kernel(s), size(s) {
	if (size < 0) {
		size = 3;
	}
}


void KernelWalker::runAlgorithm(Image & image) {
	int imageWidth = image.getWidth();
	int imageHeight = image.getHeight();

	int offset = (size - 1) / 2;

	int loopHeight = imageHeight - offset;
	int loopWidth = imageWidth - offset;

	Image source(image);
	unsigned char * srcDataPtr = source.getDataPointer();
	unsigned char * dstDataPtr = image.getDataPointer();

	for (int y = offset; y < loopHeight; y++) {
		for (int x = offset; x < loopWidth; x++) {
			int pos = (y * imageWidth + x) * 3;
			
			for (int i = 0; i < 3; i++) {
				for (int ny = 0; ny < size; ny++) {
					int correctY = y - offset + ny;

					for (int nx = 0; nx < size; nx++) {
						int correctX = x - offset + nx;
						kernel.set(nx, ny, srcDataPtr[(correctY * imageWidth + correctX) * 3 + i]);
					}
				}

				dstDataPtr[pos + i] = doAlgorithm();
			}
		}
	}
}