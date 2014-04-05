#include "Kernel.h"

Kernel::Kernel(int size): size(size) {
	// Minimum kernel size is 3.
	if (size < 3) {
		size = 3;
	}

	// Initialize kernel.
	data = new int[size * size];
}

Kernel::Kernel(Kernel & kernel) {
	*this = kernel;
}

Kernel & Kernel::operator=(const Kernel & k) {
	// Delete old data.
	delete[] data;

	// Initialize values.
	data = new int[size * size];
	size = k.size;

	int s = size * size;

	// Copy every kernel value.
	for (int i = 0; i < s; i++) {
		data[i] = k.data[i];
	}

	// Return this.
	return *this;
}


Kernel::~Kernel() {
	// Delete data.
	delete[] data;
}

int Kernel::get(int x, int y) {
	// To prevent index out of bounds, check Bounds.
	if (isInBounds(x, y)) {
		return data[y * size + x];
	}
}

void Kernel::set(int x, int y, int value) {
	// To prevent index out of bounds, check Bounds.
	if (isInBounds(x, y)) {
		data[y * size + x] = value;
	}
}

bool Kernel::isInBounds(int x, int y) {
	// To prevent index out of bounds, check Bounds.
	if (x < size && y < size) {
		return true;
	}

	return false;
}