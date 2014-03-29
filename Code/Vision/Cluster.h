#ifndef CLUSTER_H
#define CLUSTER_H

class Cluster {
public:
	Cluster();

	void add(int r, int g, int b);
	void emptyCluster();

	int getCenterR();
	int getCenterG();
	int getCenterB();

	bool recalculateCenter();
private:
	int center[3];

	int total[3];
	int amount = 0;
};

#endif