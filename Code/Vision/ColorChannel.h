#ifndef COLORCHANNEL_H
#define COLORCHANNEL_H

class ColorChannel {
public:
	ColorChannel(unsigned char * d, int s) : data(d), size(s) { };

	unsigned char * getDataPointer() { return data; }
	
	int getSize() { return size;  }
private:
	unsigned char * data;
	
	int size;
};

#endif