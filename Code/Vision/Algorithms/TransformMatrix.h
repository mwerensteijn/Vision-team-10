#ifndef TRANSFORMMATRIX_H
#define TRANSFORMMATRIX_H

#include "../Image.h"
#include <math.h>

class TransformMatrix {
public:
	static void doAlgorithm(Image & image, int interpolationOrder) {
		// Image width and height.
		int width = image.getWidth();
		int height = image.getHeight();

		// To keep the source values we temporary create a destination image which we will later copy back in the source.
		Image destination = Image(image.getWidth(), image.getHeight());

		// Pointers to access data.
		unsigned char * sourceDataPtr = image.getDataPointer();
		unsigned char * destDataPtr = destination.getDataPointer();

		double rotation = 15 * 3.1415926535897 / 180.0;
		double mask[9] = { std::cos(rotation), -std::sin(rotation), 0, std::sin(rotation), std::cos(rotation), 0, 0, 0, 1 };
		
		// If the matrix doesn't has an inverse, backwards mapping will not be possible.
		if (hasInverse(mask)) {
			// Inverse the 3x3 matrix.
			inverse3x3Matrix(mask);

			// For all pixels in the image.
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

					if (interpolationOrder == 1) {
						int sourceXLeft = std::floor(sourceX);
						int sourceXRight = std::round(sourceX);

						int sourceYTop = std::floor(sourceX);
						int sourceYBottom = std::round(sourceX);


					}
					else {
						// Interpolation order 0.
						sourceX = std::round(sourceX);
						sourceY = std::round(sourceY);
					}

					// Only change the pixel if the location of the pixel exists in the source image.
					if (sourceX < width && sourceY < height && sourceX >= 0 && sourceY >= 0) {
						// Calculate the positions to be used in a single array.
						int sourcePos = (sourceY * width + sourceX) * 3;
						int destPos = (y * width + x) * 3;
						
						// Copy the pixel.
						destDataPtr[destPos] = sourceDataPtr[sourcePos];
						destDataPtr[destPos + 1] = sourceDataPtr[sourcePos + 1];
						destDataPtr[destPos + 2] = sourceDataPtr[sourcePos + 2];
					}
				}
			}
		}

		// Copy the image back to the parameter.
		image = destination;
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

	static void fordwardMapping(Image & image) {
		double rotation = 15 * 3.1415926535897 / 180.0;

		double mask[3][3] = { { std::cos(rotation), -std::sin(rotation), 0 },
		{ std::sin(rotation), std::cos(rotation), 0 },
		{ 0, 0, 1 } };

		Image destination = Image(image.getWidth(), image.getHeight());

		int width = image.getWidth();
		int height = image.getHeight();

		unsigned char * sourceDataPtr = image.getDataPointer();
		unsigned char * destDataPtr = destination.getDataPointer();

		int pixels = width * height;
		char * pixelsEdited = new char[pixels];
		for (int i = 0; i < pixels; i++) {
			pixelsEdited[i] = 0;
		}

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				int newX = mask[0][0] * x +
					mask[0][1] * y +
					mask[0][2];

				int newY = mask[1][0] * x +
					mask[1][1] * y +
					mask[1][2];

				if (newX < width && newY < height && newX >= 0 && newY >= 0) {
					int oldPos = (y * image.getWidth() + x) * 3;
					int newPos = (newY * image.getWidth() + newX) * 3;
					destDataPtr[newPos] = sourceDataPtr[oldPos];
					destDataPtr[newPos + 1] = sourceDataPtr[oldPos + 1];
					destDataPtr[newPos + 2] = sourceDataPtr[oldPos + 2];

					pixelsEdited[newPos / 3] = 1;
				}
			}
		}

		for (int i = 0; i < pixels; i++) {
			if (pixelsEdited[i] == 0) {
				// NU DE PIXEL AANPASSEN MET INTERPOLATIE
			}
		}

		delete[] pixelsEdited;

		image = destination;
	}

};

#endif