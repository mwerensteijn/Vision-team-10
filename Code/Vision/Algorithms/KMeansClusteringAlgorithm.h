#ifndef KMEANSCLUSTERINGALGORITHM_H
#define KMEANSCLUSTERINGALGORITHM_H

#include "../Image.h"
#include "../Cluster.h"

class KMeansClusteringAlgorithm {
public:
	static void doAlgorithm(Image & image, int kAmount, int maxIterations = 25) {	
		// Get image data.
		unsigned char * dataPtr = image.getDataPointer();
		
		// Get the image size, multiplied by 3 because of R, G and B.
		int imageSize = image.getWidth() * image.getHeight() * 3;

		// Create the clusters.
		Cluster * clusters = new Cluster[kAmount];

		bool stop = false; // Do i have to stop?
		int iteration = 0; // Amount of iterations in the while loop.
		while (!stop) {
			// For every pixel in the image.
			for (int i = 0; i < imageSize; i += 3) {
				int closestCluster = 0;
				int distance = getDistance(dataPtr[i], dataPtr[i + 1], dataPtr[i + 3], clusters[0].getCenterR(), clusters[0].getCenterG(), clusters[0].getCenterB());

				// For every cluster.
				for (int a = 1; a < kAmount; a++) {
					// Calculate the distance between the pixel and the center of the cluster.
					int d = getDistance(dataPtr[i], dataPtr[i + 1], dataPtr[i + 3], clusters[a].getCenterR(), clusters[a].getCenterG(), clusters[a].getCenterB());

					// If the distance is smaller, the pixel maybe belongs to this cluster.
					if (d < distance) {
						distance = d;
						closestCluster = a;
					}
				}

				// Add R, G and B from the current pixel to the closest cluster.
				clusters[closestCluster].add(dataPtr[i], dataPtr[i + 1], dataPtr[i + 2]);
			}

			bool noChange = true;
			for (int i = 0; i < kAmount; i++) {
				if (clusters[i].recalculateCenter()) {
					// The cluster its center has changed.
					noChange = false;
				}

				clusters[i].emptyCluster();
			}

			if (noChange) {
				// The centers of all clusters haven't been changed, we can stop looping.
				stop = true;
			}

			if (++iteration == maxIterations) {
				// Max iterations reached, stop looping.
				stop = true;
			}
		}

		// For every pixel in the image.
		for (int i = 0; i < imageSize; i += 3) {
			int closestCluster = 0;
			int distance = getDistance(dataPtr[i], dataPtr[i + 1], dataPtr[i + 3], clusters[0].getCenterR(), clusters[0].getCenterG(), clusters[0].getCenterB());
			
			// Get the closest cluster.
			for (int a = 1; a < kAmount; a++) {
				int d = getDistance(dataPtr[i], dataPtr[i + 1], dataPtr[i + 3], clusters[a].getCenterR(), clusters[a].getCenterG(), clusters[a].getCenterB());

				if (d < distance) {
					distance = d;
					closestCluster = a;
				}
			}

			// Change the pixel color to the center of the closests cluster.
			dataPtr[i] = clusters[closestCluster].getCenterR();
			dataPtr[i + 1] = clusters[closestCluster].getCenterG();
			dataPtr[i + 2] = clusters[closestCluster].getCenterB();
		}

		delete[] clusters;
	}

	// This is how you calculate the distance of two xyz coordinates.
	static int getDistance(int r1, int g1, int b1, int r2, int g2, int b2) {
		int arg1 = std::pow(r2 - r1, 2);
		int arg2 = std::pow(g2 - g1, 2);
		int arg3 = std::pow(b2 - b1, 2);
		
		return std::sqrt(arg1 + arg2 + arg3);
	}
};

#endif