#ifndef CLUSTER_H
#define CLUSTER_H

class Cluster {
public:
	// Default constructor.
	Cluster();	

	// Add pixel to the cluster.
	void add(int r, int g, int b);	
	// Remove all pixels from the cluster.
	void emptyCluster();	

	// Get the centers for R, G or B.
	int getCenterR();	
	int getCenterG();	
	int getCenterB();	

	// Recalculate the average of the pixels in the cluster.
	bool recalculateCenter();	
private:
	// Holds the centers of the cluster.
	int center[3];	

	// Holds the total amount of R, G and B.
	int total[3];	
	// Amount of pixels added to the cluster.
	int amount = 0;	
};

#endif