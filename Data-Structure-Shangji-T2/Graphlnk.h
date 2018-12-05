//Graphlnk.h

# ifndef __G_H__
# define __G_H__

# include<iostream>
# include"LinkedQueue.h"
# include<string>

using namespace std;

int const maxValueDefault = 1000;

template<class T, class E>
struct Edge {	// �ߵĽ��Ķ���
	int dest;	// �ߵ���һ������λ��
	E cost;		// ���ϵ�Ȩֵ
	Edge<T, E> * link;	// ��һ���ߵ�ָ��

	Edge() { }	// ���캯��
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
	T data;				// ��������֣���ţ�
	Edge<T, E> * adj;	//�������ͷָ��


	/*	��ʾ:
	*	�����var�ǵ���ͼ�У�ÿ����ĸ�������
	*/
	string id;					// ��Ŷ�Ӧ�Ķ��㣨���㣩���
	string name;					// ��Ŷ�Ӧ�Ķ��㣨���㣩����
	string desc;					// ��Ŷ�Ӧ�Ķ��㣨���㣩���
};

template<class T, class E>
class Graphlnk {
public:
	Graphlnk(int sz);		// ���캯��
	~Graphlnk();			// ��������

	T getValue(int i) {		// ȡλ��Ϊi�Ķ����ֵ
		return (i >= 0 && i < this->NumVertices) ? this->NodeTable[i].data : 0;
	}
	string getid(int i) {		// ȡλ��Ϊi�Ķ����ֵ
		return (i >= 0 && i < this->NumVertices) ? this->NodeTable[i].id : NULL;
	}
	string getname(int i) {		// ȡλ��Ϊi�Ķ����ֵ
		return (i >= 0 && i < this->NumVertices) ? this->NodeTable[i].name : NULL;
	}
	string getdesc(int i) {		// ȡλ��Ϊi�Ķ����ֵ
		return (i >= 0 && i < this->NumVertices) ? this->NodeTable[i].desc : NULL;
	}

	void changeVertexInfor(int i, string id, string name, string desc) {
		this->NodeTable[i].id = id;
		this->NodeTable[i].name = name;
		this->NodeTable[i].desc = desc;
	}


	E getWeight(int v1, int v2);		// ���ر�(v1, v2)�ϵ�Ȩֵ

	int NumberOfVertices() {			// ��ȡ��������ע�⣺�˶�����������˼ά��
		return this->NumVertices;
	}

	int NumberOfEdges() {				// ��ȡ������ע�⣺�˱���������˼ά��
		return this->numEdges;
	}

	void ShortestPath(Graphlnk<T, E> &G, T v, E * dist, int * path);
	void printShortestPath(Graphlnk<T, E> &G, int v, E * dist, int * path);

	bool insertVertex(const T &vertex, string id, string name, string desc);	// ��ͼ�в���һ������vertex
	bool removeVertex(int v);					// ��ͼ��ɾ��һ������v
	bool insertEdge(int v1, int v2, E cost);	// ����һ����(v1, v2)
	bool removeEdge(int v1, int v2);			// ɾ��һ����(v1, v2)
	int getFirstNeighbor(int v);				// ȡ����v�ĵ�һ���ڽӶ���
	int getNextNeighbor(int v, int w);			// ȡv���ڽӶ���w����һ���ڽ�

	int getVertexPos(const T vertex) {
		for (int i = 0; i < this->NumVertices; i++) {
			if (this->NodeTable[i].data == vertex) return i;
		}
		return -1;
	}

private:
	Vertex<T, E> * NodeTable;		// �����

	int NumVertices;					// ������
	int numEdges;						// ����
	int maxVertices;					// ������ɶ�����
	int maxValue;						// Ȩֵ���������ֵ
};

template<class T, class E>
Graphlnk<T, E>::Graphlnk(int sz) {
	// ���캯��������һ���յ��ڽӱ�
	this->maxValue = maxValueDefault;
	this->maxVertices = sz;
	this->NumVertices = 0;
	this->numEdges = 0;
	this->NodeTable = new Vertex<T, E>[this->maxVertices];		// �����յĶ��������

	if (NodeTable == NULL) {
		cout << "Error: no space created !" << endl;
		exit(1);
	}

	for (int i = 0; i < maxVertices; i++) {						// ��ʼ��������ָ��ΪNULL
		this->NodeTable[i].adj = NULL;
	}

}

template<class T, class E>
Graphlnk<T, E>::~Graphlnk() {
	// ����������ɾ��˽�е��ڽӱ�
	for (int i = 0; i < NumVertices; i++) {
		Edge<T, E> * p = NodeTable[i].adj;	// �ҵ���Ӧ������׽��
		while (p != NULL) {					// ����ɾ����һ�����
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}
	delete[] this->NodeTable;
}

template<class T, class E>
E Graphlnk<T, E>::getWeight(int v1, int v2) {
	// �������ر�(v1, v2)�ϵ�Ȩֵ
	// ���ı߲���ͼ�У��򷵻�0
	if (v1 != -1 && v2 != -1) {
		Edge<T, E> * p = this->NodeTable[v1].adj;
		while (p != NULL && p->dest != v2) {
			p = p->link;
		}
		if (p != NULL) return p->cost;	// �ҵ��˱ߣ�����Ȩֵ
	}

	return 0;							// ��(v1, v2)������
}

template<class T, class E>
bool Graphlnk<T, E>::insertVertex(const T &vertex, string id, string name, string desc) {
	// ��ͼ�Ķ�����в���һ���¶���vertex��������ɹ�����true�����򷵻�false
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
	// ��ͼ��ɾ��һ��ָ������v��v�Ƕ����
	if (this->NumVertices == 1 || v < 0 || v >= this->NumVertices) {
		cout << "Error : can't remove !" << endl;
		return false;
	}

	Edge<T, E> * p;
	Edge<T, E> * s;
	Edge<T, E> * t;
	int i;
	int k;

	while (NodeTable[v].adj != NULL) {	// ɾ����v������������ж���
		p = NodeTable[v].adj;	// p��Ϊv�����������
		k = p->dest;			// ȡ�ڽӶ���k

		s = NodeTable[k].adj;	// s��Ϊk�����������
		t = NULL;				// �ҶԳƴ�ŵı߽��
		while (s != NULL && s->dest != v) {
			t = s;
			s = s->link;
		}
		if (s != NULL) {		// ����ʱs->dest == v
								// ɾ���Գƴ�ŵı߽��
								// ����Ϊ��ɾ������v�����������
								// Ҳ˵������·Ϊ��·
								// �ò�������Ϊ�˽���·����
			if (t == NULL) {
				this->NodeTable[k].adj = s->link;
			}
			else {
				t->link = s->link;	// t��linkĿǰ������s����һ����
									// ��Ϊ��ʱ��s->dest == v
									// ����v��Ҫ��ɾ���ģ����ԣ�sҲ��Ҫ��ɾ����
									// ���ԣ�t->linkӦ��ָ�� s->link
				delete s;
			}
		}
		this->NodeTable[v].adj = p->link;	// v����������߸���Ϊ��һ����
		delete p;							// �Ѷ�Ӧ�߸�ɾ��
		this->numEdges--;					// �붥��v������ı���-1
	}
	this->NumVertices--;			// ͼ�Ķ�����-1

	/*	��ʾ��
	*	
	*	���濪ʼ��һ������
	*	
	*	ע�⣺��һ��whileѭ���Ѿ�����
	*/

	NodeTable[v].data = NodeTable[NumVertices].data;	// ���
	p = NodeTable[v].adj = NodeTable[NumVertices].adj;	// ��Ҳ����
	NodeTable[v].id = NodeTable[NumVertices].id;		// ��Ҳ����
	NodeTable[v].name = NodeTable[NumVertices].name;	// ��Ҳ����
	NodeTable[v].desc = NodeTable[NumVertices].desc;	// ��Ҳ����

	while (p != NULL) {
		s = NodeTable[p->dest].adj;	// v����ָ��ı� �� dest���� �� �ڽӱ� �� ָ��ı�
		while (s != NULL) {
			if (s->dest == NumVertices) {
				s->dest = v;		// �����sָ��Ķ��������NumVertices���͸ĳ�ָ�����v
				break;
			}
			else {
				s = s->link;
			}
		}
		// ��������Ŀ����Ϊ�˱���˽���ڽӱ����飩�г��ֿ�ȱ�����Խ����һ���������������v��

		// ������һ������ı��� 
		p = p->link;
	}
	return true;
}

template<class T, class E>
bool Graphlnk<T, E>::insertEdge(int v1, int v2, E weight) {
	// �ڴ�Ȩͼ�в���һ����(v1, v2)
	// ��������Ѿ����ڻ򲻺�����������false
	if (v1 >= 0 && v1 < NumVertices && v2 >= 0 && v2 < NumVertices) {
		Edge<T, E> * q;
		Edge<T, E> * p = NodeTable[v1].adj;		// v1��Ӧ�ı�����ͷָ��
		while (p != NULL && p->dest != v2) {	// Ѱ���ڽӵ�v2
			p = p->link;
		}
		if (p != NULL) {	// �ҵ��˱�(���˱��Ѿ�����)�������룬��Ϊ��ʱp->dest = v2
			return false;
		}
		// ע�⣺whileѭ��֮��p == NULL
		// ���򴴽��½��
		p = new Edge<T, E>;
		q = new Edge<T, E>;

		p->dest = v2;	// p�����ߵ�ָ���Ƕ���v2
		p->cost = weight;
		p->link = NodeTable[v1].adj;	// ǿ����q��Edge������v2�ı�������v1->v2
										// NodeTable[v2].adj�� Edge * ��ָ��
		NodeTable[v1].adj = p;			// NodeTable[v2].adj = q ����½��

		q->dest = v1;	// q������ָ�����v1
		q->cost = weight;
		q->link = NodeTable[v2].adj;	//��v2->v1
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
	// ��ͼ��ɾ��һ����(v1, v2)
	if (v1 == -1 || v2 == -1) {
		return false;
	}

	Edge<T, E> * p = NodeTable[v1].adj;
	Edge<T, E> * q = NULL;
	Edge<T, E> * s = p;
	while (p != NULL && p->dest != v2) {	// v1�ı��������ұ�ɾ��
		q = p;		// ����ǰһ����
		p = p->link;
	}
	if (p != NULL) {	// �ҵ���ɾ��
		if (p == s) {	// ���Ǹ���
			NodeTable[v1].adj = p->link;
		}
		else {
			q->link = p->link;	// �����������ָ��v2�������ı�
								// q->link = p->link �Ӷ�����v2��ָ��ı�
		}
		delete p;
	}
	else {
		return false;	// û���ҵ���ɾ��
	}
	// �������ҵ���ɾ�ߣ�ɾ���˱�֮��Ĳ���

	// v2��Ӧ��������ɾ��
	p = NodeTable[v2].adj;
	q = NULL;
	s = p;
	while (p->dest != v1) {	// Ѱ�ұ�ɾ�߽��
		q = p;
		p = p->link;
	}
	if (p == s) {
		NodeTable[v2].adj = p->link;	// �ý���Ǳ�������׽��
	}
	else {
		q->link = p->link;				// q->link = p->link �Ӷ�����v1��ָ��ı�
	}
	delete p;
}

template<class T, class E>
int Graphlnk<T, E>::getFirstNeighbor(int v) {
	// ��������λ��Ϊv�ĵ�һ���ڽӶ����λ��
	// ����Ҳ�������������-1
	if (v != -1) {
		Edge<T, E> * p = NodeTable[v].adj;	// ��Ӧ�������һ���߽��
		if (p != NULL) {
			// ��ʱp != NULL��˵��NodeTable[v].adj����ָ��ı�
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
	// ����v���ڽӶ���w���ڽӶ����λ��
	// ��û����һ�����㣬�򷵻�-1
	if (v != -1) {
		Edge<T, E> * p = NodeTable[v].adj;	// ��Ӧ�������һ���߽��
		while (p != NULL && p->dest != w) {
			p = p->link;
		}
		// ����p->dest == w����p�����ָ��w
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
	// �Ӷ���v��������ͼG����������ȱ�����������
	int i;
	int loc;
	int n = G.NumberOfVertices();	// ȡͼ�ж���ĸ���
	bool * visited = new bool[n];		// ������������
	for (i = 0; i < n; i++) visited[i] = false;		// ��ʼ����������
	loc = G.getVertexPos(v);			// ��ȡ����λ��
	DFS(G, loc, visited);
	delete[] visited;
}

template<class T, class E>
void DFS(Graphlnk<T, E> &G, int v, bool * visited) {	// �ӹ���
														// �Ӷ���v��������������ȵĴ���������пζ������δ���ʵĶ���
														// �㷨�õ�һ����������visited�������з��ʹ��Ķ��������
	cout << "The visited vertex now: " << G.getValue(v) << endl;
	cout << "The visited vertex now: " << G.getid(v) << endl;
	cout << "The visited vertex now: " << G.getname(v) << endl;
	cout << "The visited vertex now: " << G.getdesc(v) << endl;

	visited[v] = true;

	int w = G.getFirstNeighbor(v);
	while (w != -1) {	// ����ڽӶ������
		if (visited[w] == false) {
			DFS(G, w, visited);
		}
		w = G.getNextNeighbor(v, w);	// ȡv����w�����һ���ڽӶ���
	}
}

template<class T, class E>
void BFS(Graphlnk<T, E> &G, const T &v) {
	// �Ӷ���v�������Բ������ȵĴ����������ͼ���㷨��ʹ����һ������
	int i;
	int w;
	int n = G.NumberOfVertices();	// ȡͼ�ж���ĸ���

	bool * visited = new bool[n];				// visited��¼�����Ƿ���ʹ�
	for (i = 0; i < n; i++) visited[i] = false;	// ��ʼ��

	int loc = G.getVertexPos(v);
	cout << "The vertex visited now is : " << loc << endl;
	cout << "The visited vertex now: " << G.getid(loc) << endl;
	cout << "The visited vertex now: " << G.getname(loc) << endl;
	cout << "The visited vertex now: " << G.getdesc(loc) << endl;

	visited[loc] = true;

	LinkedQueue<int> Q;
	Q.EnQueue(loc);					// ��������У�ʵ�ֲַ����
	while (!Q.isEmpty()) {
		Q.DeQueue(loc);				// �Ӷ������˳�����loc
		w = G.getFirstNeighbor(loc);// w�������ĵ�һ���ڽӶ���
		while (w != -1) {			// ���ڽӶ������
			if (visited[w] == false) {
				cout << "The visited vertex is : " << w << endl;
				cout << "The visited vertex now: " << G.getid(w) << endl;
				cout << "The visited vertex now: " << G.getname(w) << endl;
				cout << "The visited vertex now: " << G.getdesc(w) << endl;

				visited[w] = true;
				Q.EnQueue(w);		// ����w������
			}
			w = G.getNextNeighbor(loc, w);	// ��w����һ���ڽӶ���
											// ע�⣬���whileѭ��ͨ������ʵ���˷ֲ������������ȱ�������˼��
											// ��Ϊ��������ǰ��loc�������ڽӵ㶼�ŵ��˶�����
											// ע�⣬�������Ƚ��ȳ���
		}
	}
	delete[] visited;
}

template<class T, class E>
void Components(Graphlnk<T, E> &G) {
	// ��������������أ�DFS��
	// �ҵ�����ͼ��������ͨ����
	int i;
	int n = G.NumberOfVertices();

	bool * visited = new bool[n];

	for (i = 0; i < n; i++) visited[i] = false;		// ��ʼ������ʾ���ж���δ���ʹ�

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
	// Graphlnk ��һ����Ȩ����ͼ
	// ���㷨����һ�����飺dist[j], 0<=j<n���ǵ�ǰ�󵽵ĴӶ���v������j�����·������
	// ͬʱ������path[j]��0<=j<n������󵽵����·��

	int n = G.NumberOfVertices();	// �õ�������

	bool * S = new bool[n];			// ���·�����㼯
	int i;
	int j;
	int k;
	E w;
	E min;

	// �ⲿ�ֳ�ʼ����dist�����path����
	for (i = 0; i < n; i++) {
		dist[i] = G.getWeight(v, i);	// �����ʼ�����õ���Ӧ��Ȩ��
		S[i] = false;					// S���鶼��ʼ��Ϊfalse

		if (i != v && dist[i] < maxValue) path[i] = v;
		else path[i] = -1;
	}

	S[v] = true;						// ����v���붥�㼯��
	dist[v] = 0;						// (v, v)��Ȼ������0

	int u;
	for (i = 0; i < n - 1; i++) {		// ѡ����S�о������·���Ķ���u

		min = maxValue;					// ��ʼ��min
		u = v;							// ��ʼ��u

		for (j = 0; j < n; j++) {
			if (S[j] == false && dist[j] < min) {
				u = j;
				min = dist[j];
			}
		}
		S[u] = true;					// ������u���뼯��S	// ��Ϊ��ʱu��v���
		for (k = 0; k < n; k++) {		// �޸�
			w = G.getWeight(u, k);
			if (S[k] == false && w < maxValue && dist[u] + w < dist[k]) {
				// ����kδ����S�����ƹ�u��������·��
				dist[k] = dist[u] + w;	// �޸ĵ�k�����·��
				path[k] = u;			// �޸ĵ�k�����·��
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

			while (j != v) {	// d[..]���Ѽ����·���о����Ķ���
				d[k++] = j;
				j = path[j];
			}

			cout << "�Ӷ���" << G.getValue(v) << " ������" << G.getValue(i) << "�����·��Ϊ��" << G.getValue(v) << " ";
			while (k > 0) {
				cout << G.getValue(d[--k]) << " ";
			}
			cout << "���·���ĳ���Ϊ��" << dist[i] << endl;

		}
	}

	delete[] d;
}

# endif