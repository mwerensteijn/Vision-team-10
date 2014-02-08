#include <iostream>
#include "FreeImage.h"

using namespace std;

int main() {
	FreeImage_Initialise();

	const char * filename = "img.jpg";

	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(filename);

	if (fif != FIF_UNKNOWN) {
		FIBITMAP * bitmap = FreeImage_Load(fif, filename);
		RGBQUAD color;

		const int BITMAP_WIDTH = FreeImage_GetWidth(bitmap);
		const int BITMAP_HEIGHT = FreeImage_GetHeight(bitmap);

		color.rgbRed = 255;
		color.rgbGreen = 0;
		color.rgbBlue = 0;

		FreeImage_SetPixelColor(bitmap, 1, 1, &color);
		FreeImage_Save(FIF_PNG, bitmap, "filename.png", 0);
	}
	else 
	{
		cout << "Bestandsformaat is niet bekend bij de FreeImage library of het bestand kon niet worden gevonden.\n";
		cin.get();
	}

	FreeImage_DeInitialise();
	return 0;
}