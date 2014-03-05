#include "Image.h"

Image::Image(std::string filename) {
	FreeImage_Initialise();

	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(filename.c_str());

	if (fif != FIF_UNKNOWN) {
		FIBITMAP * bitmap = FreeImage_Load(fif, filename.c_str());
			
		width = FreeImage_GetWidth(bitmap);
		height = FreeImage_GetHeight(bitmap);

		data = new unsigned char[width * height * 3];
		unsigned char * ptr = data;

		RGBQUAD pixel;
			
		for (int y = 0; y < height; y++) {
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

Image::~Image() {
	if (loaded) {
		delete[] data;
	}

	FreeImage_DeInitialise();
}

int Image::getWidth() {
	return width;
}

int Image::getHeight() {
	return height;
}

void Image::saveImage(std::string filename) {
	if (loaded) {
		FIBITMAP * bitmap = FreeImage_Allocate(width, height, 24);

		unsigned char * ptr = data;

		RGBQUAD pixel;
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				pixel.rgbRed = ptr[0];
				pixel.rgbGreen = ptr[1];
				pixel.rgbBlue = ptr[2];

				ptr += 3;

				FreeImage_SetPixelColor(bitmap, x, y, &pixel);
			}
		}

		FreeImage_Save(FIF_JPEG, bitmap, filename.c_str(), 0);
	}
}