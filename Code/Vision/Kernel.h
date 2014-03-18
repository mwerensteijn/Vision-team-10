#ifndef KERNEL_H
#define KERNEL_H

class Kernel {
public:
	Kernel(int size);
	Kernel(Kernel & kernel);
	~Kernel();

	Kernel & operator=(const Kernel & k);

	int get(int x, int y);
	void set(int x, int y, int value);
	int * getDataPtr() { return data; }
	int getSize() { return size; }
private:
	int * data;
	int size;

	bool isInBounds(int x, int y);
};

#endif