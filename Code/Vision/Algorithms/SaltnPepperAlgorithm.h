#ifndef SALTNPEPPERALGORITHM_H
#define SALTNPEPPERALGORITHM_H
#define FILTER_WEAKNESS 20

class SaltnPepperAlgorithm {
public:
	static void doAlgorithm(Image & image) {
		int size = image.getWidth() * image.getHeight() * 3;

		unsigned char * ptr = image.getDataPointer();
		int j;
		for (int x = 0; x < size; x += 3) {
			j = rand() % FILTER_WEAKNESS;
			if (j == 10) {
				ptr[0] = 255;
				ptr[1] = 255;
				ptr[2] = 255;
			}
			else if (j == 0) {
				ptr[0] = 0;
				ptr[1] = 0;
				ptr[2] = 0;
			}

			ptr += 3;
		}
	}
};

#endif