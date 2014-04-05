#include "Image.h"

Image::Image(int w, int h) {
	// Image loaded is true.
	loaded = true;

	// Initialize values.
	width = w;
	height = h;

	int size = width * height * 3;
	data = new unsigned char[size];
	unsigned char * ptr = data;

	// Make every pixel black.
	for (int i = 0; i < size; i++) {
		ptr[i] = 0;
	}
}

Image::Image(std::string filename) {
	// Get the FIF for the given file. Fif contains the file type. For example: FIF_JPEG, FIF_BMP.
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(filename.c_str());

	if (fif != FIF_UNKNOWN) {
		// Load the image.
		FIBITMAP * bitmap = FreeImage_Load(fif, filename.c_str());

		// Set the width and height.
		width = FreeImage_GetWidth(bitmap);
		height = FreeImage_GetHeight(bitmap);

		data = new unsigned char[width * height * 3];
		unsigned char * ptr = data;

		// pixel holds the RGB values.
		RGBQUAD pixel;

		// For every pixel in the image, copy the values to the array.
		for (int y = height; y > 0; y--) {
			for (int x = 0; x < width; x++) {
				FreeImage_GetPixelColor(bitmap, x, y, &pixel);

				ptr[0] = pixel.rgbRed;
				ptr[1] = pixel.rgbGreen;
				ptr[2] = pixel.rgbBlue;
				ptr += 3;
			}
		}

		loaded = true;
	}
	else
	{
		loaded = false;
	}
}

Image::Image(const Image & image) {
	*this = image;
}

Image & Image::operator=(const Image & image) {
	// Only delete if the data has been initialized(= new unsigned char[size]).
	if (loaded) {
		delete[] data;
	}

	loaded = image.loaded;

	width = image.width;
	height = image.height;

	int size = width * height * 3;
	data = new unsigned char[size];

	// Copy every pixel.
	for (int i = 0; i < size; i++) {
		data[i] = image.data[i];
	}

	return *this;
}

Image::~Image() {
	// Only delete if the data has been initialized(= new unsigned char[size]).
	if (loaded) {
		delete[] data;
	}
}

int Image::getWidth() {
	return width;
}

int Image::getHeight() {
	return height;
}

void Image::saveImage(std::string filename, bool r, bool g, bool b) {
	if (loaded) {
		// Create a bitmap to hold the image.
		FIBITMAP * bitmap = FreeImage_Allocate(width, height, 24);

		unsigned char * ptr = data;

		// pixel holds a single pixel(RGB).
		RGBQUAD pixel;
		for (int y = height; y > 0; y--) {
			for (int x = 0; x < width; x++) {
				if (r) {
					pixel.rgbRed = ptr[0];
				}
				else {
					pixel.rgbRed = 0;
				}

				if (g) {
					pixel.rgbGreen = ptr[1];
				}
				else {
					pixel.rgbGreen = 0;
				}

				if (b) {
					pixel.rgbBlue = ptr[2];
				}
				else {
					pixel.rgbBlue = 0;
				}

				ptr += 3;

				FreeImage_SetPixelColor(bitmap, x, y, &pixel);
			}
		}

		filename += ".bmp";

		// Save the image using BMP format.
		FreeImage_Save(FIF_BMP, bitmap, filename.c_str(), 0);
	}
}


void Image::saveImageRed(std::string filename) {
	saveImage(filename, true, false, false);
}

void Image::saveImageGreen(std::string filename) {
	saveImage(filename, false, true, false);
}

void Image::saveImageBlue(std::string filename) {
	saveImage(filename, false, false, true);

}