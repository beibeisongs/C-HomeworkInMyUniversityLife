// Test.cpp

# include<iostream>
# include"Graphlnk.h"

using namespace std;

int main() {

	/*	功能记录：
	*	（1） 查询各景点的相关信息							-pass 
	*	（2） 查询图中任意两个景点间的最短路径				-pass		
	*	（3） 查询图中任意两个景点间的所有路径				-pass
	*	（4） 增加、删除、更新有关景点和道路的信息			-pass
	*	（5） 求从某源点出发到多个景点的最佳（最短）游览路径	-pass
	*/

	Graphlnk<int, int> G1(5);

	/*	
	*	增加景点信息
	*/
	int i0 = 0;
	G1.insertVertex(i0, "000", "000", "000");
	int i1 = 1;
	G1.insertVertex(i1, "111", "111", "111");

	/*
	*	增加景点道路信息
	*/
	int weight = 1;
	G1.insertEdge(i0, i1, weight);

	int k3 = G1.getFirstNeighbor(i0);
	cout << "i0 's first neighbor : " << k3 << endl;

	int i2 = 2;
	weight = 2;
	G1.insertVertex(i2, "222", "222", "222");
	G1.insertEdge(i0, i2, weight);

	/*
	*	查询景点信息（此处为深度优先遍历 和 广度优先遍历）
	*/
	cout << "深度优先遍历：" << endl;
	DFS<int, int>(G1, i0);
	cout << "广度优先遍历：" << endl;
	BFS<int, int>(G1, i0);
	cout << "遍历结束：" << endl;

	/*
	*	查询图中任意两个景点间的最短路径
	*/
	int v1 = G1.getVertexPos(1);
	int v2 = G1.getVertexPos(2);
	weight = 4;
	G1.insertEdge(v1, v2, weight);
	
	int n = G1.NumberOfVertices();	// 得到顶点数
	int * dist = new int[n];
	int * path = new int[n];
	G1.ShortestPath(G1, v1, dist, path);
	G1.printShortestPath(G1, v1, dist, path);

	/*
	*	查询图中任意两个景点间的所有路径
	*/
	int ** allpaths = new int * [n];
	for (int i = 0; i < n; i++) {
		allpaths[i] = new int[n];	// 记录初始化
		for (int j = 0; j < n; j++) {
			allpaths[i][j] = -1;
		}
	}

	G1.findAllPaths(G1, v1, v2, dist, allpaths);
	cout << "现在输出：" << v1 << " 到 " << v2 << " 的所有路径" << endl;
	for (int i = 0; i < n; i++) {
		if (allpaths[i][0] != -1) {
			cout << "从点 " << v1;

			for (int j = 0; j < n; j++) {
				if (allpaths[i][j] != -1) {
					cout << "到 " << allpaths[i][j] << " ";

					if (allpaths[i][j] == v2) break;
				}

			} cout << endl;
		}
	}


	/*
	*	查询图中指定两个景点间的最短路径
	*/
	v1 = G1.getVertexPos(1);
	v2 = G1.getVertexPos(2);
	G1.ShortestPath(G1, v1, dist, path);
	G1.printShortestPath(G1, v1, v2, dist, path);

	/*
	*	删除景点信息
	*/
	v1 = G1.getVertexPos(i1);
	G1.removeVertex(v1);

	/*
	*	删除景点道路信息
	*/
	v1 = G1.getVertexPos(0);
	v2 = G1.getVertexPos(2);
	G1.removeEdge(v1, v2);

	/*
	*	更新景点信息
	*/
	int v0 = G1.getVertexPos(0);
	G1.changeVertexInfo(v0, "00", "00", "00");

	Components<int, int>(G1);

	int mark;
	cout << "Please input the mark you like : " << endl;
	cin >> mark;

	return 0;
}
