#ifndef KERNEL_H
#define KERNEL_H

class Kernel {
public:
	// Constructors.
	Kernel(int size);			// Constructor(kernelSize);
	Kernel(Kernel & kernel);	// Copy Constructor.
	~Kernel();					// Deconstructor.

	// Assignment operator.
	Kernel & operator=(const Kernel & k);

	// Get and set values at specific positions in the kernel.
	int get(int x, int y);
	void set(int x, int y, int value);

	// Return pointer, pointing to the kernel values.
	int * getDataPtr() { return data; }

	// Return kernelWidth and kernelHeight.
	int getSize() { return size; }
private:
	// Holds the kernel values.
	int * data;
	// Holds the kernelWidth and kernelHeight.
	int size;

	// To check if a given position is within the kernelWidth and kernelHeight.
	bool isInBounds(int x, int y);
};

#endif