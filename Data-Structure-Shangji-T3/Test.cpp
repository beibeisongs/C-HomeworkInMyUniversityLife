// Test.cpp

# include<iostream>
# include"Graphlnk.h"

using namespace std;

int main() {

	Graphlnk<int, int> G1(5);

	int i0 = 0;
	G1.insertVertex(i0, "000", "000", "000");
	int i1 = 1;
	G1.insertVertex(i1, "111", "111", "111");


	int weight = 1;
	G1.insertEdge(i0, i1, weight);

	int k3 = G1.getFirstNeighbor(i0);
	cout << "i0 's first neighbor : " << k3 << endl;

	int i2 = 2;
	weight = 2;
	G1.insertVertex(i2, "222", "222", "222");
	G1.insertEdge(i0, i2, weight);

	cout << "深度优先遍历：" << endl;
	DFS<int, int>(G1, i0);
	cout << "广度优先遍历：" << endl;
	BFS<int, int>(G1, i0);
	cout << "遍历结束：" << endl;

	int v1 = G1.getVertexPos(1);
	int v2 = G1.getVertexPos(2);
	weight = 4;
	G1.insertEdge(v1, v2, weight);

	/*
	*	测试Prim算法
	*	
	*	测试最短路径
	*/
	
	int n = G1.NumberOfVertices();		// 得到顶点数
	int * dist = new int[n];
	int * path = new int[n];
	int * path2 = new int[n];

	Prim(G1, v1, dist, path2);
	printPrimPath(path2);

	G1.ShortestPath(G1, v1, dist, path);
	G1.printShortestPath(G1, v1, dist, path);

	v1 = G1.getVertexPos(1);
	v2 = G1.getVertexPos(2);
	G1.ShortestPath(G1, v1, dist, path);
	G1.printShortestPath(G1, v1, v2, dist, path);

	v1 = G1.getVertexPos(i1);
	G1.removeVertex(v1);

	v1 = G1.getVertexPos(0);
	v2 = G1.getVertexPos(2);
	G1.removeEdge(v1, v2);

	int v0 = G1.getVertexPos(0);
	G1.changeVertexInfor(v0, "00", "00", "00");

	Components<int, int>(G1);

	int mark;
	cout << "Please input the mark you like : " << endl;
	cin >> mark;

	return 0;
}