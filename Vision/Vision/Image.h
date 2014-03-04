#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <fstream>
#include "FreeImage.h"

class Image {
public:
	Image(std::string filename);
	~Image();

	bool isLoaded() { return loaded; };

	int getWidth();
	int getHeight();

	char * getDataPointer() { return data; }

	void saveImage(std::string filename);
private:
	bool loaded;

	char* data;

	int width;
	int height;
};

#endif