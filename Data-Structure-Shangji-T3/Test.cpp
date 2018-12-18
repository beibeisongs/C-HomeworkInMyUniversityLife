// Test.cpp

# include<iostream>
# include"Graphlnk.h"

using namespace std;

int main() {
	/*
	Graphlnk<int, int> G1(5);

	int i0 = 0;
	G1.insertVertex(i0, "000", "地点0", "居民楼0");
	int i1 = 1;
	G1.insertVertex(i1, "001", "地点1", "居民楼1");


	int weight = 1;
	G1.insertEdge(i0, i1, weight);

	int k3 = G1.getFirstNeighbor(i0);
	cout << "i0 's first neighbor : " << k3 << endl;

	int i2 = 2;
	weight = 2;
	G1.insertVertex(i2, "002", "地点2", "居民楼2");
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
	*/

	/* 测试数据如图：[..]中的是结点，边上的值是权值，注：根据题意，本图设计为无向图

	(0,1)=10
	(1,2)=50
	(2,3)=30
	(3,4)=60
	(4,0)=100
	(0,3)=30
	(2,4)=10


				[0]
			-	    -		-100
		-10			   -			-
	[1]				     -30				[4]
			-				-	  -10	60-
				50-		-	  -		-
					 [2] -20-	 [3]
	*/

	Graphlnk<int, int> G1(5);

	/*
	*	增加景点信息
	*/
	int i0 = 0;
	G1.insertVertex(i0, "000", "景点0", "公园");
	int i1 = 1;
	G1.insertVertex(i1, "001", "景点1", "小池");
	int i2 = 2;
	G1.insertVertex(i2, "002", "景点2", "花园");
	int i3 = 3;
	G1.insertVertex(i3, "003", "景点3", "小桥");
	int i4 = 4;
	G1.insertVertex(i4, "004", "景点4", "古楼");


	/*
	*	增加景点道路信息
	*/
	int weight = 10;
	G1.insertEdge(i0, i1, weight);

	//int k3 = G1.getFirstNeighbor(i0);
	//cout << "i0 's first neighbor : " << k3 << endl;

	weight = 50;
	G1.insertEdge(i1, i2, weight);
	weight = 20;
	G1.insertEdge(i2, i3, weight);
	weight = 60;
	G1.insertEdge(i3, i4, weight);
	weight = 100;
	G1.insertEdge(i4, i0, weight);
	weight = 10;
	G1.insertEdge(i2, i4, weight);
	weight = 30;
	G1.insertEdge(i0, i3, weight);

	/*
	*	测试Prim算法
	*	
	*	测试最短路径
	*/
	
	int n = G1.NumberOfVertices();		// 得到顶点数
	int * dist = new int[n];
	int * path = new int[n];
	int * path2 = new int[n];

	int v1 = i1;
	int v2 = i2;

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