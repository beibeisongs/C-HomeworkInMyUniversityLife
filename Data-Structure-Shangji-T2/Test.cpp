// Test.cpp

# include<iostream>
# include"Graphlnk.h"

using namespace std;

int main() {

	int maxValue = 1000;

	/*	���ܼ�¼��
	*	��1�� ��ѯ������������Ϣ							-pass 
	*	��2�� ��ѯͼ�������������������·��				-pass		
	*	��3�� ��ѯͼ��������������������·��				-pass
	*	��4�� ���ӡ�ɾ���������йؾ���͵�·����Ϣ			-pass
	*	��5�� ���ĳԴ�����������������ѣ���̣�����·��	-pass
	*/

	Graphlnk<int, int> G1(5);

	/*	
	*	���Ӿ�����Ϣ
	*/
	int i0 = 0;
	G1.insertVertex(i0, "000", "����0", "��԰");
	int i1 = 1;
	G1.insertVertex(i1, "001", "����1", "С��");
	int i2 = 2;
	G1.insertVertex(i2, "002", "����2", "��԰");
	int i3 = 3;
	G1.insertVertex(i3, "003", "����3", "С��");
	int i4 = 4;
	G1.insertVertex(i4, "004", "����4", "��¥");


	/*
	*	���Ӿ����·��Ϣ
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
	*	��ѯ������Ϣ���˴�Ϊ������ȱ��� �� ������ȱ�����
	*/
	cout << "������ȱ�����" << endl;
	DFS<int, int>(G1, i0);
	cout << "������ȱ�����" << endl;
	BFS<int, int>(G1, i0);
	cout << "����������" << endl;

	/*
	*	��ѯͼ�������������������·��
	*/
	int v1 = G1.getVertexPos(1);
	int v2 = G1.getVertexPos(2);
	
	int n = G1.NumberOfVertices();	// �õ�������
	int * dist = new int[n];
	for (int i = 0; i < n; i++) {	// dist�����ʼ��
		dist[i] = maxValue;
	}

	int * path = new int[n];
	for (int i = 0; i < n; i++) {	// path�����ʼ��
		path[i] = -1;
	}
	G1.ShortestPath(G1, v1, dist, path);
	G1.printShortestPath(G1, v1, dist, path);

	/*
	*	��ѯͼ��������������������·��
	*/
	int ** allpaths = new int * [n];
	for (int i = 0; i < n; i++) {
		allpaths[i] = new int[n];	// ��¼��ʼ��
		for (int j = 0; j < n; j++) {
			allpaths[i][j] = -1;
		}
	}

	G1.findAllPaths(G1, v1, v2, dist, allpaths);
	cout << "���������" << v1 << " �� " << v2 << " ������·��" << endl;
	for (int i = 0; i < n; i++) {
		if (allpaths[i][0] != -1) {
			cout << "�ӵ� " << v1;

			for (int j = 0; j < n; j++) {
				if (allpaths[i][j] != -1) {
					cout << "�� " << allpaths[i][j] << " ";

					if (allpaths[i][j] == v2) break;
				}

			} cout << endl;
		}
	}


	/*
	*	��ѯͼ��ָ���������������·��
	*/
	v1 = G1.getVertexPos(1);
	v2 = G1.getVertexPos(2);
	G1.ShortestPath(G1, v1, dist, path);
	G1.printShortestPath(G1, v1, v2, dist, path);

	/*
	*	ɾ��������Ϣ
	*/
	v1 = G1.getVertexPos(i1);
	G1.removeVertex(v1);

	/*
	*	ɾ�������·��Ϣ
	*/
	v1 = G1.getVertexPos(0);
	v2 = G1.getVertexPos(2);
	G1.removeEdge(v1, v2);

	/*
	*	���¾�����Ϣ
	*/
	int v0 = G1.getVertexPos(0);
	G1.changeVertexInfo(v0, "008", "�¾���0", "��԰");

	Components<int, int>(G1);

	int mark;
	cout << "Please input the mark you like : " << endl;
	cin >> mark;

	return 0;
}