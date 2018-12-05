//Graphlnk.h

# ifndef __G_H__
# define __G_H__

# include<iostream>
# include"LinkedQueue.h"
# include<string>

using namespace std;

int const maxValueDefault = 1000;

template<class T, class E>
struct Edge {	// 边的结点的定义
	int dest;	// 边的另一个顶点位置
	E cost;		// 边上的权值
	Edge<T, E> * link;	// 下一条边的指针

	Edge() { }	// 构造函数
	Edge(int num, E weight) {
		this->dest = num;
		this->cost = weight;
		this->link = NULL;
	}
	bool operator != (Edge<T, E> &R) {
		return (this->dest != R.dest) ? true : false;
	}
};

template<class T, class E>
struct Vertex {
	T data;				// 顶点的名字（序号）
	Edge<T, E> * adj;	//边链表的头指针


	/*	提示:
	*	下面的var是导游图中，每个点的各个属性
	*/
	string id;					// 存放对应的顶点（景点）编号
	string name;					// 存放对应的顶点（景点）名称
	string desc;					// 存放对应的顶点（景点）简介
};

template<class T, class E>
class Graphlnk {
public:
	Graphlnk(int sz);		// 构造函数
	~Graphlnk();			// 析构函数

	T getValue(int i) {		// 取位置为i的顶点的值
		return (i >= 0 && i < this->NumVertices) ? this->NodeTable[i].data : 0;
	}
	string getid(int i) {		// 取位置为i的顶点的值
		return (i >= 0 && i < this->NumVertices) ? this->NodeTable[i].id : NULL;
	}
	string getname(int i) {		// 取位置为i的顶点的值
		return (i >= 0 && i < this->NumVertices) ? this->NodeTable[i].name : NULL;
	}
	string getdesc(int i) {		// 取位置为i的顶点的值
		return (i >= 0 && i < this->NumVertices) ? this->NodeTable[i].desc : NULL;
	}

	void changeVertexInfor(int i, string id, string name, string desc) {
		this->NodeTable[i].id = id;
		this->NodeTable[i].name = name;
		this->NodeTable[i].desc = desc;
	}


	E getWeight(int v1, int v2);		// 返回边(v1, v2)上的权值

	int NumberOfVertices() {			// 获取顶点数（注意：此顶点数是人类思维）
		return this->NumVertices;
	}

	int NumberOfEdges() {				// 获取边数（注意：此边数是人类思维）
		return this->numEdges;
	}

	void ShortestPath(Graphlnk<T, E> &G, T v, E * dist, int * path);
	void printShortestPath(Graphlnk<T, E> &G, int v, E * dist, int * path);

	bool insertVertex(const T &vertex, string id, string name, string desc);	// 在图中插入一个顶点vertex
	bool removeVertex(int v);					// 在图中删除一个顶点v
	bool insertEdge(int v1, int v2, E cost);	// 插入一条边(v1, v2)
	bool removeEdge(int v1, int v2);			// 删除一条边(v1, v2)
	int getFirstNeighbor(int v);				// 取顶点v的第一个邻接顶点
	int getNextNeighbor(int v, int w);			// 取v的邻接顶点w的下一个邻接

	int getVertexPos(const T vertex) {
		for (int i = 0; i < this->NumVertices; i++) {
			if (this->NodeTable[i].data == vertex) return i;
		}
		return -1;
	}

private:
	Vertex<T, E> * NodeTable;		// 顶点表

	int NumVertices;					// 顶点数
	int numEdges;						// 边数
	int maxVertices;					// 最大容纳顶点数
	int maxValue;						// 权值的最大限制值
};

template<class T, class E>
Graphlnk<T, E>::Graphlnk(int sz) {
	// 构造函数，建立一个空的邻接表
	this->maxValue = maxValueDefault;
	this->maxVertices = sz;
	this->NumVertices = 0;
	this->numEdges = 0;
	this->NodeTable = new Vertex<T, E>[this->maxVertices];		// 创建空的顶点表数组

	if (NodeTable == NULL) {
		cout << "Error: no space created !" << endl;
		exit(1);
	}

	for (int i = 0; i < maxVertices; i++) {						// 初始化边链接指针为NULL
		this->NodeTable[i].adj = NULL;
	}

}

template<class T, class E>
Graphlnk<T, E>::~Graphlnk() {
	// 析构函数：删除私有的邻接表
	for (int i = 0; i < NumVertices; i++) {
		Edge<T, E> * p = NodeTable[i].adj;	// 找到对应链表的首结点
		while (p != NULL) {					// 不断删除第一个结点
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}
	delete[] this->NodeTable;
}

template<class T, class E>
E Graphlnk<T, E>::getWeight(int v1, int v2) {
	// 函数返回边(v1, v2)上的权值
	// 若改边不在图中，则返回0
	if (v1 != -1 && v2 != -1) {
		Edge<T, E> * p = this->NodeTable[v1].adj;
		while (p != NULL && p->dest != v2) {
			p = p->link;
		}
		if (p != NULL) return p->cost;	// 找到此边，返回权值
	}

	return 0;							// 边(v1, v2)不存在
}

template<class T, class E>
bool Graphlnk<T, E>::insertVertex(const T &vertex, string id, string name, string desc) {
	// 在图的顶点表中插入一个新顶点vertex，若插入成功返回true，否则返回false
	if (this->NumVertices == this->maxVertices) {
		return false;
	}
	this->NodeTable[this->NumVertices].data = vertex;
	this->NodeTable[this->NumVertices].id = id;
	this->NodeTable[this->NumVertices].name = name;
	this->NodeTable[this->NumVertices].desc = desc;

	this->NumVertices++;

	return true;
}

template<class T, class E>
bool Graphlnk<T, E>::removeVertex(int v) {
	// 在图中删除一个指定顶点v，v是顶点号
	if (this->NumVertices == 1 || v < 0 || v >= this->NumVertices) {
		cout << "Error : can't remove !" << endl;
		return false;
	}

	Edge<T, E> * p;
	Edge<T, E> * s;
	Edge<T, E> * t;
	int i;
	int k;

	while (NodeTable[v].adj != NULL) {	// 删除第v个边链表的所有顶点
		p = NodeTable[v].adj;	// p成为v引向的那条边
		k = p->dest;			// 取邻接顶点k

		s = NodeTable[k].adj;	// s成为k引向的那条边
		t = NULL;				// 找对称存放的边结点
		while (s != NULL && s->dest != v) {
			t = s;
			s = s->link;
		}
		if (s != NULL) {		// 即此时s->dest == v
								// 删除对称存放的边结点
								// 这是为了删除连向v顶点的那条边
								// 也说明，该路为回路
								// 该操作就是为了将回路剪开
			if (t == NULL) {
				this->NodeTable[k].adj = s->link;
			}
			else {
				t->link = s->link;	// t的link目前保存了s的下一条边
									// 因为此时，s->dest == v
									// 而，v是要被删掉的，所以，s也是要被删掉的
									// 所以，t->link应该指向 s->link
				delete s;
			}
		}
		this->NodeTable[v].adj = p->link;	// v引向的那条边更新为下一条边
		delete p;							// 把对应边给删了
		this->numEdges--;					// 与顶点v相关联的边数-1
	}
	this->NumVertices--;			// 图的顶点数-1

	/*	提示：
	*	
	*	下面开始下一步处理
	*	
	*	注意：上一个while循环已经结束
	*/

	NodeTable[v].data = NodeTable[NumVertices].data;	// 填补点
	p = NodeTable[v].adj = NodeTable[NumVertices].adj;	// 边也补上
	NodeTable[v].id = NodeTable[NumVertices].id;		// 边也补上
	NodeTable[v].name = NodeTable[NumVertices].name;	// 边也补上
	NodeTable[v].desc = NodeTable[NumVertices].desc;	// 边也补上

	while (p != NULL) {
		s = NodeTable[p->dest].adj;	// v顶点指向的边 的 dest顶点 的 邻接表 的 指向的边
		while (s != NULL) {
			if (s->dest == NumVertices) {
				s->dest = v;		// 即如果s指向的顶点是序号NumVertices，就改成指向序号v
				break;
			}
			else {
				s = s->link;
			}
		}
		// 这样做的目的是为了避免私有邻接表（数组）中出现空缺，所以将最后一个顶点链补到序号v处

		// 继续下一个顶点的遍历 
		p = p->link;
	}
	return true;
}

template<class T, class E>
bool Graphlnk<T, E>::insertEdge(int v1, int v2, E weight) {
	// 在带权图中插入一条边(v1, v2)
	// 若插入边已经存在或不合理，函数返回false
	if (v1 >= 0 && v1 < NumVertices && v2 >= 0 && v2 < NumVertices) {
		Edge<T, E> * q;
		Edge<T, E> * p = NodeTable[v1].adj;		// v1对应的边链表头指针
		while (p != NULL && p->dest != v2) {	// 寻找邻接点v2
			p = p->link;
		}
		if (p != NULL) {	// 找到此边(即此边已经存在)，不插入，因为此时p->dest = v2
			return false;
		}
		// 注意：while循环之后p == NULL
		// 否则创建新结点
		p = new Edge<T, E>;
		q = new Edge<T, E>;

		p->dest = v2;	// p这条边的指向是顶点v2
		p->cost = weight;
		p->link = NodeTable[v1].adj;	// 强调：q是Edge，链入v2的边链表，即v1->v2
										// NodeTable[v2].adj是 Edge * 型指针
		NodeTable[v1].adj = p;			// NodeTable[v2].adj = q 这个新结点

		q->dest = v1;	// q这条边指向的是v1
		q->cost = weight;
		q->link = NodeTable[v2].adj;	//即v2->v1
		NodeTable[v2].adj = q;

		numEdges++;

		return true;
	}
	else {
		return false;
	}
}

template<class T, class E>
bool Graphlnk<T, E>::removeEdge(int v1, int v2) {
	// 在图中删除一条边(v1, v2)
	if (v1 == -1 || v2 == -1) {
		return false;
	}

	Edge<T, E> * p = NodeTable[v1].adj;
	Edge<T, E> * q = NULL;
	Edge<T, E> * s = p;
	while (p != NULL && p->dest != v2) {	// v1的边链表中找被删边
		q = p;		// 储存前一个边
		p = p->link;
	}
	if (p != NULL) {	// 找到被删边
		if (p == s) {	// 这是个环
			NodeTable[v1].adj = p->link;
		}
		else {
			q->link = p->link;	// 现在这个边是指向v2这个顶点的边
								// q->link = p->link 从而接上v2所指向的边
		}
		delete p;
	}
	else {
		return false;	// 没有找到被删边
	}
	// 下面是找到被删边，删除了边之后的操作

	// v2对应边链表中删除
	p = NodeTable[v2].adj;
	q = NULL;
	s = p;
	while (p->dest != v1) {	// 寻找被删边结点
		q = p;
		p = p->link;
	}
	if (p == s) {
		NodeTable[v2].adj = p->link;	// 该结点是边链表的首结点
	}
	else {
		q->link = p->link;				// q->link = p->link 从而接上v1所指向的边
	}
	delete p;
}

template<class T, class E>
int Graphlnk<T, E>::getFirstNeighbor(int v) {
	// 给出顶点位置为v的第一个邻接顶点的位置
	// 如果找不到，则函数返回-1
	if (v != -1) {
		Edge<T, E> * p = NodeTable[v].adj;	// 对应边链表第一个边结点
		if (p != NULL) {
			// 此时p != NULL，说明NodeTable[v].adj有它指向的边
			return p->dest;
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}
}

template<class T, class E>
int Graphlnk<T, E>::getNextNeighbor(int v, int w) {
	// 给出v的邻接顶点w的邻接顶点的位置
	// 若没有下一个顶点，则返回-1
	if (v != -1) {
		Edge<T, E> * p = NodeTable[v].adj;	// 对应链表的下一个边结点
		while (p != NULL && p->dest != w) {
			p = p->link;
		}
		// 现在p->dest == w，即p这个边指向w
		if (p != NULL && p->link != NULL) {
			return p->link->dest;
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}
}

template<class T, class E>
void DFS(Graphlnk<T, E> &G, const T &v) {
	// 从顶点v出发，对图G进行深度优先遍历的主过程
	int i;
	int loc;
	int n = G.NumberOfVertices();	// 取图中顶点的个数
	bool * visited = new bool[n];		// 创建辅助数组
	for (i = 0; i < n; i++) visited[i] = false;		// 初始化辅助数组
	loc = G.getVertexPos(v);			// 获取顶点位置
	DFS(G, loc, visited);
	delete[] visited;
}

template<class T, class E>
void DFS(Graphlnk<T, E> &G, int v, bool * visited) {	// 子过程
														// 从顶点v出发，以深度优先的次序访问所有课读入的尚未访问的顶点
														// 算法用到一个辅助数组visited，对所有访问过的顶点做标记
	cout << "The visited vertex now: " << G.getValue(v) << endl;
	cout << "The visited vertex now: " << G.getid(v) << endl;
	cout << "The visited vertex now: " << G.getname(v) << endl;
	cout << "The visited vertex now: " << G.getdesc(v) << endl;

	visited[v] = true;

	int w = G.getFirstNeighbor(v);
	while (w != -1) {	// 如果邻接顶点存在
		if (visited[w] == false) {
			DFS(G, w, visited);
		}
		w = G.getNextNeighbor(v, w);	// 取v排在w后的下一个邻接顶点
	}
}

template<class T, class E>
void BFS(Graphlnk<T, E> &G, const T &v) {
	// 从顶点v出发，以层序优先的次序横向搜索图，算法中使用了一个队列
	int i;
	int w;
	int n = G.NumberOfVertices();	// 取图中顶点的个数

	bool * visited = new bool[n];				// visited记录顶点是否访问过
	for (i = 0; i < n; i++) visited[i] = false;	// 初始化

	int loc = G.getVertexPos(v);
	cout << "The vertex visited now is : " << loc << endl;
	cout << "The visited vertex now: " << G.getid(loc) << endl;
	cout << "The visited vertex now: " << G.getname(loc) << endl;
	cout << "The visited vertex now: " << G.getdesc(loc) << endl;

	visited[loc] = true;

	LinkedQueue<int> Q;
	Q.EnQueue(loc);					// 顶点进队列，实现分层访问
	while (!Q.isEmpty()) {
		Q.DeQueue(loc);				// 从队列中退出顶点loc
		w = G.getFirstNeighbor(loc);// w这个顶点的第一个邻接顶点
		while (w != -1) {			// 若邻接顶点存在
			if (visited[w] == false) {
				cout << "The visited vertex is : " << w << endl;
				cout << "The visited vertex now: " << G.getid(w) << endl;
				cout << "The visited vertex now: " << G.getname(w) << endl;
				cout << "The visited vertex now: " << G.getdesc(w) << endl;

				visited[w] = true;
				Q.EnQueue(w);		// 顶点w进队列
			}
			w = G.getNextNeighbor(loc, w);	// 找w的下一个邻接顶点
											// 注意，这个while循环通过队列实现了分层遍历（广度优先遍历）的思想
											// 因为，它将当前的loc的所有邻接点都放到了队列中
											// 注意，队列是先进先出的
		}
	}
	delete[] visited;
}

template<class T, class E>
void Components(Graphlnk<T, E> &G) {
	// 利用深度优先搜素（DFS）
	// 找到无向图的所有连通分量
	int i;
	int n = G.NumberOfVertices();

	bool * visited = new bool[n];

	for (i = 0; i < n; i++) visited[i] = false;		// 初始化，表示所有顶点未访问过

	cout << endl;
	cout << "This is the process to visit all the components : " << endl;

	for (i = 0; i < n; i++) {
		if (visited[i] == false) {
			DFS<T, E>(G, i, visited);
		}
	}
	delete[] visited;
}

template<class T, class E>
void Graphlnk<T, E>::ShortestPath(Graphlnk<T, E> &G, T v, E * dist, int * path) {
	// Graphlnk 是一个带权有向图
	// 本算法建立一个数组：dist[j], 0<=j<n，是当前求到的从顶点v到顶点j的最短路径长度
	// 同时用数组path[j]，0<=j<n，存放求到的最短路径

	int n = G.NumberOfVertices();	// 得到顶点数

	bool * S = new bool[n];			// 最短路径顶点集
	int i;
	int j;
	int k;
	E w;
	E min;

	// 这部分初始化了dist数组和path数组
	for (i = 0; i < n; i++) {
		dist[i] = G.getWeight(v, i);	// 数组初始化，得到对应的权重
		S[i] = false;					// S数组都初始化为false

		if (i != v && dist[i] < maxValue) path[i] = v;
		else path[i] = -1;
	}

	S[v] = true;						// 顶点v加入顶点集合
	dist[v] = 0;						// (v, v)固然距离是0

	int u;
	for (i = 0; i < n - 1; i++) {		// 选不在S中具有最短路径的顶点u

		min = maxValue;					// 初始化min
		u = v;							// 初始化u

		for (j = 0; j < n; j++) {
			if (S[j] == false && dist[j] < min) {
				u = j;
				min = dist[j];
			}
		}
		S[u] = true;					// 将顶点u加入集合S	// 因为此时u到v最短
		for (k = 0; k < n; k++) {		// 修改
			w = G.getWeight(u, k);
			if (S[k] == false && w < maxValue && dist[u] + w < dist[k]) {
				// 顶点k未加入S，且绕过u可以缩短路径
				dist[k] = dist[u] + w;	// 修改到k的最短路径
				path[k] = u;			// 修改到k的最短路径
			}
		}
	}
}

template<class T, class E>
void Graphlnk<T, E>::printShortestPath(Graphlnk<T, E> &G, int v, E * dist, int * path) {
	int i;
	int j;
	int k;
	int n = G.NumberOfVertices();

	int * d = new int[n];
	for (i = 0; i < n; i++) {

		if (i != v) {

			j = i;
			k = 0;

			while (j != v) {	// d[..]在搜集最短路径中经过的顶点
				d[k++] = j;
				j = path[j];
			}

			cout << "从顶点" << G.getValue(v) << " 到顶点" << G.getValue(i) << "的最短路径为：" << G.getValue(v) << " ";
			while (k > 0) {
				cout << G.getValue(d[--k]) << " ";
			}
			cout << "最短路径的长度为：" << dist[i] << endl;

		}
	}

	delete[] d;
}

# endif