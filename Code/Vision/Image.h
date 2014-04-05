#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <fstream>
#include "FreeImage.h"
#include "ColorChannel.h"

class Image {
public:
	// Constructors.
	Image(int width, int height);	// Constructor(width, height);
	Image(std::string filename);	// Constructor(filename);
	Image(const Image & image);		// Copy constructor.
	~Image();						// Deconstructor.
	
	// Asignment operator.
	Image & operator=(const Image & image);
	
	// Has the image been loaded.
	bool isLoaded() { return loaded; };

	// Return width and height.
	int getWidth();
	int getHeight();

	// Return the pointer, pointing to the RGB values.
	unsigned char * getDataPointer() { return data; }

	// Return the channels for R, G and B.
	ColorChannel getRedChannel() { return ColorChannel(data, width * height); }
	ColorChannel getGreenChannel() { return ColorChannel(data + 1, width * height); }
	ColorChannel getBlueChannel() { return ColorChannel(data + 2, width * height); }

	// Save the image, or individual color channels.
	void saveImage(std::string filename, bool r = true, bool g = true, bool b = true);
	void saveImageRed(std::string filename);
	void saveImageGreen(std::string filename);
	void saveImageBlue(std::string filename);

	// Load the FreeImage library.
	static void loadLibrary() { FreeImage_Initialise(); }
	// Unload the FreeImage library.
	static void unloadLibrary() { FreeImage_DeInitialise(); }
private:
	// Has the image been loaded?
	bool loaded;

	// Points towards the RGB values.
	unsigned char* data;

	// Width and height of the image.
	int width;
	int height;
};

#endif