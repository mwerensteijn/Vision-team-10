#include <iostream>
#include "FreeImage.h"

using namespace std;

void inverse_image(FIBITMAP * bitmap);
void grayscale_image(FIBITMAP * bitmap);

int main() {
	FreeImage_Initialise();

	const char * filename = "img.jpg";

	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(filename);

	if (fif != FIF_UNKNOWN) {
		FIBITMAP * bitmap = FreeImage_Load(fif, filename);

		grayscale_image(bitmap);

		FreeImage_Save(FIF_JPEG, bitmap, "filename.jpeg", 0);
	}
	else 
	{
		cout << "Bestandsformaat is niet bekend bij de FreeImage library of het bestand kon niet worden gevonden.\n";
		cin.get();
	}

	FreeImage_DeInitialise();
	return 0;
}

void inverse_image(FIBITMAP * bitmap) {
	RGBQUAD pixel;

	const int BITMAP_WIDTH = FreeImage_GetWidth(bitmap);
	const int BITMAP_HEIGHT = FreeImage_GetHeight(bitmap);

	for (int y = 0; y < BITMAP_HEIGHT; y++) {
		for (int x = 0; x < BITMAP_WIDTH; x++) {
			FreeImage_GetPixelColor(bitmap, x, y, &pixel);

			pixel.rgbRed = ~pixel.rgbRed;
			pixel.rgbGreen = ~pixel.rgbGreen;
			pixel.rgbBlue = ~pixel.rgbBlue;

			FreeImage_SetPixelColor(bitmap, x, y, &pixel);
		}
	}
}

// Source: http://tech.pro/tutorial/660/csharp-tutorial-convert-a-color-image-to-grayscale
void grayscale_image(FIBITMAP * bitmap) {
	RGBQUAD pixel;

	const int BITMAP_WIDTH = FreeImage_GetWidth(bitmap);
	const int BITMAP_HEIGHT = FreeImage_GetHeight(bitmap);

	for (int y = 0; y < BITMAP_HEIGHT; y++) {
		for (int x = 0; x < BITMAP_WIDTH; x++) {
			FreeImage_GetPixelColor(bitmap, x, y, &pixel);

			int grayscale = (pixel.rgbRed * .3) + (pixel.rgbGreen * .59) + (pixel.rgbBlue * .11);
			pixel.rgbRed = grayscale;
			pixel.rgbGreen = grayscale;
			pixel.rgbBlue = grayscale;

			FreeImage_SetPixelColor(bitmap, x, y, &pixel);
		}
	}
}