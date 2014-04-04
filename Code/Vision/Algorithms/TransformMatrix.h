#ifndef TRANSFORMMATRIX_H
#define TRANSFORMMATRIX_H

#include "../Image.h"
#include <math.h>

class TransformMatrix {
public:
	static void doAlgorithm(Image & image, int interpolationOrder, std::string file) {
		// Image width and height.
		int width = image.getWidth();
		int height = image.getHeight();

		// To keep the source values we temporary create a destination image which we will later copy back in the source.
		Image * destination;

		// Pointers to access data.
		unsigned char * sourceDataPtr = image.getDataPointer();

		double mask[9];
		loadMaskFromFile(file, mask);

		// If the matrix doesn't has an inverse, backwards mapping will not be possible.
		if (hasInverse(mask)) {
			// The output image may be larger or smaller than the original.
			int newWidth = 0;
			int newHeight = 0;

			// To calculate the right output positions.
			int minWidth = 0;
			int minHeight = 0;

			// Find the maximum and minimum values for the width and height of the output image.
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					// Find the x position in the source image.
					double sourceX = mask[0] * x +
									 mask[1] * y +
									 mask[2];

					// Find the y position in the source image.
					double sourceY = mask[3] * x +
									 mask[4] * y +
									 mask[5];

					// Is the x position bigger?
					if (sourceX > newWidth) {
						// The x position is the new maximum width.
						newWidth = sourceX;
					}
					else if (sourceX < minWidth) {
						// The x position is the new minimum width.
						minWidth = sourceX;
					}

					if (sourceY > newHeight) {
						// The y position is the new maximum height.
						newHeight = sourceY;
					}
					else if (sourceY < minHeight) {
						// The y position is the new minimum height.
						minHeight = sourceY;
					}
				}
			}

			minWidth = std::abs(minWidth);
			minHeight = std::abs(minHeight);

			// Plus 1 Because an array index starts at zero.
			newWidth += minWidth + 1;
			newHeight += minHeight + 1;

			// Create the output image with the right sizes.
			destination = new Image(newWidth, newHeight);
			unsigned char * destDataPtr = destination->getDataPointer();

			// Inverse the 3x3 matrix.
			inverse3x3Matrix(mask);

			// For all pixels in the image.
			for (int y = 0; y < newHeight; y++) {
				for (int x = 0; x < newWidth; x++) {
					// Find the x position in the source image.
					double sourceX = mask[0] * (x - minWidth) +
									 mask[1] * (y - minHeight) +
									 mask[2];

					// Find the y position in the source image.
					double sourceY = mask[3] * (x - minWidth) +
									 mask[4] * (y - minHeight) +
									 mask[5];

					// Only change the pixel if the location of the pixel exists in the source image.
					if (sourceX < width && sourceY < height && sourceX >= 0 && sourceY >= 0) {
						//std::cout << "sourceX: " << sourceX << "\tsourceY: " << sourceY << std::endl;

						int destPos = (y * newWidth + x) * 3;
						int r, g, b;

						if (interpolationOrder == 1) {
							// First interpolation order

							// X position of the left corner pixel.
							int sourceXLeft = sourceX;
							// X position of the right corner pixel.
							int sourceXRight = sourceX + 1;

							// Y position of the top corner pixel.
							int sourceYTop = sourceY;
							// Y position of the bottom corner pixel.
							int sourceYBottom = sourceY + 1;

							// Calculate the weighted percentage values for each cornel pixel.
							double percentageLeftTop = (sourceYBottom - sourceY) * (sourceXRight - sourceX);
							double percentageLeftBottom = (sourceY - sourceYTop) * (sourceXRight - sourceX);
							double percentageRightTop = (sourceX - sourceXLeft) * (sourceYBottom - sourceY);
							double percentageRightBottom = (sourceX - sourceXLeft) * (sourceY - sourceYTop);

							// Set R G B to zero.
							r = 0; g = 0; b = 0;

							// Precalulate the array position, to save cpu time.
							int arrayPos = (sourceYTop * width + sourceXLeft) * 3;
							// Add the weighted color values to the destination pixel.
							r += sourceDataPtr[arrayPos] * percentageLeftTop;
							g += sourceDataPtr[arrayPos + 1] * percentageLeftTop;
							b += sourceDataPtr[arrayPos + 2] * percentageLeftTop;
							
							// Precalulate the array position, to save cpu time.
							arrayPos = (sourceYTop * width + sourceXRight) * 3;
							// Add the weighted color values to the destination pixel.
							r += sourceDataPtr[arrayPos] * percentageRightTop;
							g += sourceDataPtr[arrayPos + 1] * percentageRightTop;
							b += sourceDataPtr[arrayPos + 2] * percentageRightTop;
							
							// Precalulate the array position, to save cpu time.
							arrayPos = (sourceYBottom * width + sourceXLeft) * 3;
							// Add the weighted color values to the destination pixel.
							r += sourceDataPtr[arrayPos] * percentageLeftBottom;
							g += sourceDataPtr[arrayPos + 1] * percentageLeftBottom;
							b += sourceDataPtr[arrayPos + 2] * percentageLeftBottom;

							// Precalulate the array position, to save cpu time.
							arrayPos = (sourceYBottom * width + sourceXRight) * 3;
							// Add the weighted color values to the destination pixel.
							r += sourceDataPtr[arrayPos] * percentageRightBottom;
							g += sourceDataPtr[arrayPos + 1] * percentageRightBottom;
							b += sourceDataPtr[arrayPos + 2] * percentageRightBottom;
						}
						else {
							// Interpolation order 0.
							sourceX = std::round(sourceX);
							sourceY = std::round(sourceY);

							// Calculate the positions to be used in a single array.
							int sourcePos = (sourceY * width + sourceX) * 3;

							// Get the source pixel
							r = sourceDataPtr[sourcePos];
							g = sourceDataPtr[sourcePos + 1];
							b = sourceDataPtr[sourcePos + 2];
						}

						if (x == 10 && y == 10) {
							//std::cout << "r: " << r << "\tg: " << g << "\tb: " << b << std::endl;
							//std::cin.get();

							destDataPtr[destPos] = 0;
							destDataPtr[destPos + 1] = 0;
							destDataPtr[destPos + 2] = 0;
						}
						else {

							// Copy the pixel.
							destDataPtr[destPos] = r;
							destDataPtr[destPos + 1] = g;
							destDataPtr[destPos + 2] = b;
						}
					}
				}
			}
		}
		else {
			// Matrix can not be inversed.
			std::cout << "The matrix can not be inversed!\n";
			std::cin.get();
		}

		// Copy the image back to the parameter.
		image = *destination;
		delete destination;
	}

	static bool hasInverse(double * matrix) {
		// Return true if the matrix has an inverse.
		return (determinant3x3Matrix(matrix) != 0);
	}

	static void inverse3x3Matrix(double * matrix) {
		// Calculating the inverse of a matrix
		// Explained: http://www.wikihow.com/Inverse-a-3X3-Matrix

		// Calculate the determinant.
		double det = determinant3x3Matrix(matrix);

		// If the determinant is zero, an inversed matrix can't be calculated.
		if (det != 0) {
			// Transpone the matrix.
			transpone3x3Matrix(matrix);

			// Make a copy of the matrix.
			double old[9];
			for (int i = 0; i < 9; i++) {
				old[i] = matrix[i];
			}

			// Find the determinant of each of the 2x2 minor matrices.
			matrix[0] = old[4] * old[8] - old[5] * old[7];
			matrix[1] = old[3] * old[8] - old[5] * old[6];
			matrix[2] = old[3] * old[7] - old[6] * old[4];

			matrix[3] = old[1] * old[8] - old[7] * old[2];
			matrix[4] = old[0] * old[8] - old[2] * old[6];
			matrix[5] = old[0] * old[7] - old[1] * old[6];

			matrix[6] = old[1] * old[5] - old[2] * old[4];
			matrix[7] = old[0] * old[5] - old[2] * old[3];
			matrix[8] = old[0] * old[4] - old[1] * old[3];

			// Multiply the matrix with each sign:
			// + - +
			// - + -
			// + - +
			// Thus, each uneven array index will be multiplied with minus 1.
			for (int i = 1; i < 9; i += 2) {
				matrix[i] *= -1;
			}

			// Multiply the adjugate with 1 divided by the determinant of the matrix.
			double value = 1 / det;
			for (int i = 0; i < 9; i++) {
				matrix[i] *= value;
			}
		}
	}

	static double determinant3x3Matrix(double * matrix) {
		// Calculate the determinant of a 3x3 matrix.
		return	matrix[0] * (matrix[4] * matrix[8] - matrix[5] * matrix[7]) -
				matrix[1] * (matrix[3] * matrix[8] - matrix[5] * matrix[6]) +
				matrix[2] * (matrix[3] * matrix[7] - matrix[4] * matrix[6]);
	}

	static void transpone3x3Matrix(double * matrix) {
		// Example of transponing
		// 1 2 3         1 0 5
		// 0 1 4   -->   2 1 6
		// 5 6 0         3 4 0

		// Make a copy of the matrix.
		double old[9];
		for (int i = 0; i < 9; i++) {
			old[i] = matrix[i];
		}

		// Transpone matrix.
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				matrix[x * 3 + y] = old[y * 3 + x];
			}
		}
	}

	static void loadMaskFromFile(std::string file, double * mask) {
		// Open the file
		std::fstream myfile(file, std::ios_base::in);

		// For every position in the matrix, read a number from the file.
		for (int i = 0; i < 9; i++) {
			myfile >> mask[i];
		}

		// Close the file.
		myfile.close();
	}

};

#endif