#ifndef __HP_H__
#define __HP_H__

#include<iostream>

using namespace std;

enum BOOL { False, True };
template<class T, class E>
class MinHeap {
public:
	MinHeap(int sz);			// 构造函数：建立空堆
	MinHeap(E arr[], int n);	// 构造函数：通过一个数组
	~MinHeap() {				// 析构函数
		delete[] heap;
	}
	bool Insert(E x);			// 将x插入到最小堆中
	bool removeMin(E &x);				// 删除堆顶元素

	bool isEmpty() const {
		return (this->currentSize == 0) ? true : false;
	}
	bool IsFull() const {
		return (this->currentSize == this->maxHeapSize) ? true : false;
	}

	void makeEmpty() {	// 置空堆
		currentSize = 0;
	}
private:
	E * heap;							// 存放最小堆中元素的数组
	int currentSize;					// 最小堆中当前的元素
	int maxHeapSize;					// 最小堆最多允许存放元素个数
	void siftDown(int start, int m);	// 从start到m下滑调整为最小堆
	void siftUp(int start);				// 从start到0上划成为最小堆
};

template<class T, class E>
MinHeap<T, E>::MinHeap(int maxHeapSize) {
	this->maxHeapSize = maxHeapSize;
	this->heap = new E[this->maxHeapSize];
	if (heap == NULL) {
		cout << "堆分配内存失败 ！" << endl;
		exit(1);
	}
	this->currentSize = 0;
}

template<class T, class E>
MinHeap<T, E>::MinHeap(E arr[], int n) {
	this->maxHeapSize = n;
	this->heap = new E[this->maxHeapSize];
	if (heap == NULL) {
		cout << "堆内存分配失败" << endl;
		exit(1);
	}
	for (int i = 0; i < n; i++) {			// 复制堆数组，建立当前大小
		this->heap[i] = arr[i];
	}
	this->currentSize = n;
	int currentPos = (currentSize - 2) / 2;	// 找最初调整位置：最后分支结点
											// 这是最后一个结点的根结点
	while (currentPos >= 0) {				// 自底向上逐步扩大形成堆
		this->siftDown(currentPos, currentSize - 1);
		currentPos--;
	}
}

template<class T, class E>
void MinHeap<T, E>::siftDown(int start, int m) {
	// 私有函数：从结点start开始到m为止，自上向下比较，如果子女的值小于父结点的值
	// 则关键码小的上浮，继续向下层比较，这样将一个集合局部调整为最小堆
	int i = start;
	int j = 2 * i + 1;	// 从而j得到i的左子节点的下标(计算机思维)
						// 请注意这个基础算法

	E temp = heap[i];	// temp被赋值当前结点值
	E job = heap[j];
	E j2 = heap[j + 1];

	while (j <= m) {
		if (j < m && job->data > j2->data) j++;	// 让j指向两子女中的小者

		if (temp->data <= job->data) break;	// 小则不做调整
		else {
			heap[i] = heap[j];		// 否则小者上移，i，j下降
			i = j;
			j = 2 * j + 1;			// j移动到它的左结点的下标(计算机思维)
		}
	}
	heap[i] = temp;					// i 要么移动过，要么保持原来的值不变
}

template<class T, class E>
bool MinHeap<T, E>::Insert(E x) {
	// 公有函数：将x插入到最小堆中
	if (this->currentSize == this->maxHeapSize) {
		cout << "Heap Full ! " << endl;
		return false;
	}
	this->heap[currentSize] = x;	// 插入
	this->siftUp(currentSize);		// 向上调整
	this->currentSize++;			// 堆计数+1

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
	// 私有函数：从结点start开始到结点0为止，自下向上比较
	// 如果子女的值小于父结点的值
	// 则相互交换，这样重新将集合调整为最小堆
	int j = start;
	int i = (j - 1) / 2;	// 因为现在是自下向上调整，所以j是最底部的那个结点
							// 该指令让i得到j的根节点的下标(计算机思维)
	E temp = heap[j];

	E job = heap[i];

	while (j > 0) {
		if (job->data <= temp->data) break;	// 父结点值小，不作调整
		else {								// 父结点值大，调整
			heap[j] = heap[i];
			j = i;							// j的值在这里被更新
			i = (i - 1) / 2;
		}
	}
	heap[j] = temp;					// 值回送
}

template<class T, class E>
bool MinHeap<T, E>::removeMin(E &x) {
	if (!this->currentSize) {	// 堆空，返回false
		cout << "Heap Empty !" << endl;
		return false;
	}
	x = heap[0];
	heap[0] = heap[currentSize - 1];
	currentSize--;
	this->siftDown(0, currentSize - 1);		// 自小向下调整为堆

	E job;
	for (int i = 0; i < this->currentSize; i++) {
		job = heap[i];
		cout << "data: " << job->data << endl;
	}
	cout << endl;

	return true;
}

#endif // __HP_H__