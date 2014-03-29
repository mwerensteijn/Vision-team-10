#include "Cluster.h"
#include <time.h>
#include <iostream>

Cluster::Cluster() {
	srand(time(NULL));

	center[0] = rand() % 255 + 1;
	center[1] = rand() % 255 + 1;
	center[2] = rand() % 255 + 1;

	total[0] = 0;
	total[1] = 0;
	total[2] = 0;
}

void Cluster::add(int r, int g, int b) {
	total[0] += r;
	total[1] += g;
	total[2] += b;

	amount++;
}

void Cluster::emptyCluster() {
	for (int i = 0; i < 3; i++) {
		total[i] = 0;
	}

	amount = 0;
}

bool Cluster::recalculateCenter() {
	bool changed = false;

	if (amount > 0) {
		int newCenterR = total[0] / amount;
		int newCenterG = total[1] / amount;
		int newCenterB = total[2] / amount;
	
		if (newCenterR != center[0] ||
			newCenterG != center[1] ||
			newCenterB != center[2]) {
			changed = true;
		}

		center[0] = newCenterR;
		center[1] = newCenterG;
		center[2] = newCenterB;
	}
	else {
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