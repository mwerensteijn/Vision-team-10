#include "Kernel.h"

Kernel::Kernel(int size): size(size) {
	if (size < 0) {
		size = 3;
	}

	data = new int[size * size];
}

Kernel::Kernel(Kernel & kernel) {
	*this = kernel;
}

Kernel & Kernel::operator=(const Kernel & k) {
	delete[] data;
	data = new int[size * size];
	size = k.size;

	int s = size * size;

	for (int i = 0; i < s; i++) {
		data[i] = k.data[i];
	}

	return *this;
}


Kernel::~Kernel() {
	delete[] data;
}

int Kernel::get(int x, int y) {
	if (isInBounds(x, y)) {
		return data[y * size + x];
	}
}

void Kernel::set(int x, int y, int value) {
	if (isInBounds(x, y)) {
		data[y * size + x] = value;
	}
}

bool Kernel::isInBounds(int x, int y) {
	if (x < size && y < size) {
		return true;
	}

	return false;
}