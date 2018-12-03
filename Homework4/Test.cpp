// Test.cpp

# include<iostream>
# include"Graphlnk.h"

using namespace std;

int main() {

	Graphlnk<int, int> G1(5);

	int i0 = 0;
	G1.insertVertex(i0);
	int i1 = 1;
	G1.insertVertex(i1);

	int weight = 1;
	
	G1.insertEdge(i0, i1, weight);

	int k3 = G1.getFirstNeighbor(i0);
	cout<< "i0 's first neighbor : "<< k3<< endl;

	// G1.removeVertex(i1);
	int i2 = 2;
	G1.insertVertex(i2);
	G1.insertEdge(i0, i2, weight);


	DFS<int, int>(G1, i0);
	
	BFS<int, int>(G1, i0);

	Components<int, int>(G1);

	int mark;
	cout<< "Please input the mark you like : "<< endl;
	cin>> mark;

	return 0;
}