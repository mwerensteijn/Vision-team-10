#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <fstream>
#include "FreeImage.h"
#include "ColorChannel.h"

class Image {
public:
	Image(int width, int height);
	Image(std::string filename);
	Image(const Image & image);
	~Image();
	
	Image & operator=(const Image & image);


	bool isLoaded() { return loaded; };

	int getWidth();
	int getHeight();

	unsigned char * getDataPointer() { return data; }

	ColorChannel getRedChannel() { return ColorChannel(data, width * height); }
	ColorChannel getGreenChannel() { return ColorChannel(data + 1, width * height); }
	ColorChannel getBlueChannel() { return ColorChannel(data + 2, width * height); }

	void saveImage(std::string filename);
	static void loadLibrary() { FreeImage_Initialise(); }
	static void unloadLibrary() { FreeImage_DeInitialise(); }
private:
	bool loaded;

	unsigned char* data;

	int width;
	int height;
};

#endif