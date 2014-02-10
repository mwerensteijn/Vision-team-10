#include <iostream>
#include <fstream>
#include "FreeImage.h"

using namespace std;

void inverse_image(FIBITMAP * bitmap);
void grayscale_image(FIBITMAP * bitmap, string filename);
int * get_grayscale_intensity_histogram(FIBITMAP * bitmap);
double * get_grayscale_density_histogram(FIBITMAP * bitmap);
void generate_frequency_histogram(FIBITMAP * bitmap, string filename);
void generate_density_histogram(FIBITMAP * bitmap, string filename);

int main() {
	FreeImage_Initialise();

	const char * filename = "img.jpg";

	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(filename);

	if (fif != FIF_UNKNOWN) {
		FIBITMAP * bitmap = FreeImage_Load(fif, filename);

		grayscale_image(bitmap, filename);
		generate_frequency_histogram(bitmap, filename);
		generate_density_histogram(bitmap, filename);
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
void grayscale_image(FIBITMAP * bitmap, string filename) {
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
	
	filename = "grey_" + filename;
	FreeImage_Save(FIF_JPEG, bitmap, filename.c_str(), 0);
}

int * get_grayscale_intensity_histogram(FIBITMAP * bitmap) {
	int * histogram = new int[256];

	RGBQUAD pixel;

	const int BITMAP_WIDTH = FreeImage_GetWidth(bitmap);
	const int BITMAP_HEIGHT = FreeImage_GetHeight(bitmap);

	for (int i = 0; i < 255; i++) {
		histogram[i] = 0;
	}

	for (int y = 0; y < BITMAP_HEIGHT; y++) {
		for (int x = 0; x < BITMAP_WIDTH; x++) {
			FreeImage_GetPixelColor(bitmap, x, y, &pixel);
			histogram[pixel.rgbRed]++;
		}
	}

	return histogram;
}

double * get_grayscale_density_histogram(FIBITMAP * bitmap) {
	double * histogram = new double[10];

	RGBQUAD pixel;

	const int BITMAP_WIDTH = FreeImage_GetWidth(bitmap);
	const int BITMAP_HEIGHT = FreeImage_GetHeight(bitmap);

	for (int i = 0; i < 10; i++) {
		histogram[i] = 0;
	}

	for (int y = 0; y < BITMAP_HEIGHT; y++) {
		for (int x = 0; x < BITMAP_WIDTH; x++) {
			FreeImage_GetPixelColor(bitmap, x, y, &pixel);
			histogram[(int)((pixel.rgbRed * 10) / 256)]++;
		}
	}

	int totaal = 0;
	for (int i = 0; i < 10; i++) {
		totaal += histogram[i];
	}

	for (int i = 0; i < 10; i++) {
		histogram[i] /= totaal;
	}

	return histogram;
}

void generate_frequency_histogram(FIBITMAP * bitmap, string filename) {
	int * histogram = get_grayscale_intensity_histogram(bitmap);
	
	filename.append("_frequency.csv");
	ofstream output(filename);
	if (output.is_open()) {
		for (int i = 0; i < 255; i++) {
			output << i << ',' << histogram[i] << endl;
		}

		output.close();
	}
}

void generate_density_histogram(FIBITMAP * bitmap, string filename) {
	double * histogram = get_grayscale_density_histogram(bitmap);

	filename.append("_density.csv");
	ofstream output(filename);
	if (output.is_open()) {
		for (int i = 0; i < 10; i++) {
			output << i << ',' << histogram[i] << endl;
		}

		output.close();
	}
}