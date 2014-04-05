#ifndef COLORCHANNEL_H
#define COLORCHANNEL_H

class ColorChannel {
public:
	// Constructor(dataPointer, imageSize);
	ColorChannel(unsigned char * d, int s) : data(d), size(s) { }; 

	// Return the data pointer.
	unsigned char * getDataPointer() { return data; }	
	
	// Return the size of the image.
	int getSize() { return size;  }
private:
	// Holds the pointer.
	unsigned char * data; 

	// Holds the size of the image.
	int size; 
};

#endif