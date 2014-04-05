#include "Cluster.h"
#include <time.h>
#include <iostream>

Cluster::Cluster() {
	// Seed the random number generator
	srand(time(NULL));

	// Select random cluster points(rgb or xyz).
	center[0] = rand() % 255 + 1;
	center[1] = rand() % 255 + 1;
	center[2] = rand() % 255 + 1;

	// Set total to 0.
	total[0] = 0;
	total[1] = 0;
	total[2] = 0;
}

void Cluster::add(int r, int g, int b) {
	// Add the rgb / xyz value to the cluster.
	total[0] += r;
	total[1] += g;
	total[2] += b;
	
	// Increase the amount of pixels added to the cluster.
	amount++;
}

void Cluster::emptyCluster() {
	// Set RGB/XYZ to 0.
	for (int i = 0; i < 3; i++) {
		total[i] = 0;
	}

	// Set the amount of pixels to 0.
	amount = 0;
}

bool Cluster::recalculateCenter() {
	bool changed = false;

	if (amount > 0) {
		// Calculate the average of the pixels in the cluster.
		int newCenterR = total[0] / amount;
		int newCenterG = total[1] / amount;
		int newCenterB = total[2] / amount;
	
		// If the center changed, return true.
		if (newCenterR != center[0] ||
			newCenterG != center[1] ||
			newCenterB != center[2]) {
			changed = true;
		}

		// Set the new centers.
		center[0] = newCenterR;
		center[1] = newCenterG;
		center[2] = newCenterB;
	}
	else {
		// There are no pixels in the cluster, therefore there can't be calculated a new center, lets randomly select centers.
		for (int i = 0; i < 3; i++) {
			center[i] = rand() % 255 + 1;
		}
	}

	return changed;
}

int Cluster::getCenterR() {
	return center[0];
}

int Cluster::getCenterG() {
	return center[1];
}

int Cluster::getCenterB() {
	return center[2];
}