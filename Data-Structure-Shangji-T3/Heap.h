#ifndef __HP_H__
#define __HP_H__

#include<iostream>

using namespace std;

enum BOOL { False, True };
template<class T, class E>
class MinHeap {
public:
	MinHeap(int sz);			// ���캯���������ն�
	MinHeap(E arr[], int n);	// ���캯����ͨ��һ������
	~MinHeap() {				// ��������
		delete[] heap;
	}
	bool Insert(E x);			// ��x���뵽��С����
	bool removeMin(E &x);				// ɾ���Ѷ�Ԫ��

	bool isEmpty() const {
		return (this->currentSize == 0) ? true : false;
	}
	bool IsFull() const {
		return (this->currentSize == this->maxHeapSize) ? true : false;
	}

	void makeEmpty() {	// �ÿն�
		currentSize = 0;
	}
private:
	E * heap;							// �����С����Ԫ�ص�����
	int currentSize;					// ��С���е�ǰ��Ԫ��
	int maxHeapSize;					// ��С�����������Ԫ�ظ���
	void siftDown(int start, int m);	// ��start��m�»�����Ϊ��С��
	void siftUp(int start);				// ��start��0�ϻ���Ϊ��С��
};

template<class T, class E>
MinHeap<T, E>::MinHeap(int maxHeapSize) {
	this->maxHeapSize = maxHeapSize;
	this->heap = new E[this->maxHeapSize];
	if (heap == NULL) {
		cout << "�ѷ����ڴ�ʧ�� ��" << endl;
		exit(1);
	}
	this->currentSize = 0;
}

template<class T, class E>
MinHeap<T, E>::MinHeap(E arr[], int n) {
	this->maxHeapSize = n;
	this->heap = new E[this->maxHeapSize];
	if (heap == NULL) {
		cout << "���ڴ����ʧ��" << endl;
		exit(1);
	}
	for (int i = 0; i < n; i++) {			// ���ƶ����飬������ǰ��С
		this->heap[i] = arr[i];
	}
	this->currentSize = n;
	int currentPos = (currentSize - 2) / 2;	// ���������λ�ã�����֧���
											// �������һ�����ĸ����
	while (currentPos >= 0) {				// �Ե������������γɶ�
		this->siftDown(currentPos, currentSize - 1);
		currentPos--;
	}
}

template<class T, class E>
void MinHeap<T, E>::siftDown(int start, int m) {
	// ˽�к������ӽ��start��ʼ��mΪֹ���������±Ƚϣ������Ů��ֵС�ڸ�����ֵ
	// ��ؼ���С���ϸ����������²�Ƚϣ�������һ�����Ͼֲ�����Ϊ��С��
	int i = start;
	int j = 2 * i + 1;	// �Ӷ�j�õ�i�����ӽڵ���±�(�����˼ά)
						// ��ע����������㷨

	E temp = heap[i];	// temp����ֵ��ǰ���ֵ
	E job = heap[j];
	E j2 = heap[j + 1];

	while (j <= m) {
		if (j < m && job->data > j2->data) j++;	// ��jָ������Ů�е�С��

		if (temp->data <= job->data) break;	// С��������
		else {
			heap[i] = heap[j];		// ����С�����ƣ�i��j�½�
			i = j;
			j = 2 * j + 1;			// j�ƶ�������������±�(�����˼ά)
		}
	}
	heap[i] = temp;					// i Ҫô�ƶ�����Ҫô����ԭ����ֵ����
}

template<class T, class E>
bool MinHeap<T, E>::Insert(E x) {
	// ���к�������x���뵽��С����
	if (this->currentSize == this->maxHeapSize) {
		cout << "Heap Full ! " << endl;
		return false;
	}
	this->heap[currentSize] = x;	// ����
	this->siftUp(currentSize);		// ���ϵ���
	this->currentSize++;			// �Ѽ���+1

	E job;
	for (int i = 0; i < this->currentSize; i++) {
		job = heap[i];
		cout << "data: " << job->data << endl;
	}
	cout << endl;

	return true;
}

template<class T, class E>
void MinHeap<T, E>::siftUp(int start) {
	// ˽�к������ӽ��start��ʼ�����0Ϊֹ���������ϱȽ�
	// �����Ů��ֵС�ڸ�����ֵ
	// ���໥�������������½����ϵ���Ϊ��С��
	int j = start;
	int i = (j - 1) / 2;	// ��Ϊ�������������ϵ���������j����ײ����Ǹ����
							// ��ָ����i�õ�j�ĸ��ڵ���±�(�����˼ά)
	E temp = heap[j];

	E job = heap[i];

	while (j > 0) {
		if (job->data <= temp->data) break;	// �����ֵС����������
		else {								// �����ֵ�󣬵���
			heap[j] = heap[i];
			j = i;							// j��ֵ�����ﱻ����
			i = (i - 1) / 2;
		}
	}
	heap[j] = temp;					// ֵ����
}

template<class T, class E>
bool MinHeap<T, E>::removeMin(E &x) {
	if (!this->currentSize) {	// �ѿգ�����false
		cout << "Heap Empty !" << endl;
		return false;
	}
	x = heap[0];
	heap[0] = heap[currentSize - 1];
	currentSize--;
	this->siftDown(0, currentSize - 1);		// ��С���µ���Ϊ��

	E job;
	for (int i = 0; i < this->currentSize; i++) {
		job = heap[i];
		cout << "data: " << job->data << endl;
	}
	cout << endl;

	return true;
}

#endif // __HP_H__