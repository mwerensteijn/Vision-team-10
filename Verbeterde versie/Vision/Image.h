#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <fstream>
#include "FreeImage.h"

class Image {
public:
	Image(std::string filename);
	Image(Image & image);
	~Image();

	Image & operator=(const Image & i);

	bool isLoaded() { return loaded; };

	int getWidth();
	int getHeight();

	unsigned char * getDataPointer() { return data; }

	void saveImage(std::string filename);
private:
	bool loaded;

	unsigned char* data;

	int width;
	int height;
};

#endif