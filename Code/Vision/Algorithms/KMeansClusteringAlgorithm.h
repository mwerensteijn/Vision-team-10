#ifndef KMEANSCLUSTERINGALGORITHM_H
#define KMEANSCLUSTERINGALGORITHM_H

#include "../Image.h"

class KMeansClusteringAlgorithm {
public:
	static void doAlgorithm(Image & image, int clusters, int maxIterations = 25) {
		// Clusters centers
		unsigned char * redClusterCenters = new unsigned char[clusters];
		unsigned char * greenClusterCenters = new unsigned char[clusters];
		unsigned char * blueClusterCenters = new unsigned char[clusters];

		// Random choosing points for the clusters.
		for (int cluster = 0; cluster < clusters; cluster++) {
			redClusterCenters[cluster] = rand() % 255 + 1;
			greenClusterCenters[cluster] = rand() % 255 + 1;
			blueClusterCenters[cluster] = rand() % 255 + 1;
		}

		// Image Access
		int imagePixels = image.getWidth() * image.getHeight();
		unsigned char * ptr = image.getDataPointer();
		unsigned char red, green, blue;

		// Amount of iterations
		int iterations = 0;
		while (true) {
			// To hold the total sum of all pixels in a cluster.
			long * redClusterSum = new long[clusters];
			long * greenClusterSum = new long[clusters];
			long * blueClusterSum = new long[clusters];

			int * clusterSumCount = new int[clusters];

			for (int pixel = 0; pixel < imagePixels; pixel++) {
				red = ptr[pixel];
				green = ptr[pixel + 1];
				blue = ptr[pixel + 2];

				int cluster = 0;
				for (int cluster = 0; cluster < clusters; cluster++) {
				//	int result = sqrt(
									//pow(red - clusterP)
				}
			}


			// Limit the amount of iterations to the maxIterations argument. Default = 25;
			if (++iterations == maxIterations) {
				break;
			}
		}


		for (int x = 0; x < imagePixels; x += 3) {
			
		}
	}
};

#endif