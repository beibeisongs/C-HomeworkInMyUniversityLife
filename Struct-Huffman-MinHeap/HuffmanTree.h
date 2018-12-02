#ifndef __H_M__
#define __H_M__

#include<iostream>
#include"Heap.h"

using namespace std;

template<class T, class E>
struct HuffmanNode {	// 树节点的类定义
	E data;				// 结点数据
	HuffmanNode<T, E> * leftChild;
	HuffmanNode<T, E> * rightChild;
	HuffmanNode<T, E> * parent;

	HuffmanNode() {		// 构造函数
		this->leftChild = NULL;
		this->rightChild = NULL;
		this->parent = NULL;
	}

	HuffmanNode(E elem,
		HuffmanNode<T, E> * left,
		HuffmanNode<T, E> * right,
		HuffmanNode<T, E> * parent) {
		
		this->data = elem;
		this->leftChild = left;
		this->rightChild = right;
		this->parent = parent;
	}

};

template<class T, class E>
class HuffmanTree {
public:
	HuffmanTree(E w[], int n);		// 构造函数
	~HuffmanTree() { }

	void Traverse(HuffmanNode<T, E> * tree);		// 使用先序遍历，输入树
	void traverse();	// 调用Traverse子步骤
protected:
	HuffmanNode<T, E> * root;		// HuffmanTree的根
	void mergeTree(HuffmanNode<T, E> * ht1,
		HuffmanNode<T, E> * ht2,
		HuffmanNode<T, E> * parent);
	
};

template<class T, class E>
HuffmanTree<T, E>::HuffmanTree(E w[], int n) {
	// 给出n个权值w[1] - w[n]，构造Huffman树
	MinHeap<T, HuffmanNode<T, E> *> hp(n);	// 使用最小堆存放森林

	HuffmanNode<T, E> * first = new HuffmanNode<T, E>;
	HuffmanNode<T, E> * second = new HuffmanNode<T, E>;
	
	HuffmanNode<T, E> ** NodeList = new HuffmanNode<T, E> * [n];	// n棵树组成的森林

	HuffmanNode<T, E> * job;

	for (int i = 0; i < n; i++) {
		NodeList[i] = new HuffmanNode<T, E>;
	}

	for (int i = 0; i < n; i++) {
		job = NodeList[i];

		job->data = w[i];
		job->leftChild = NULL;
		job->rightChild = NULL;
		job->parent = NULL;
		hp.Insert(NodeList[i]);			// 插入最小堆中
	}

	HuffmanNode<T, E> ** NodeList2 = new HuffmanNode<T, E> * [n - 1];
	for (int i = 0; i < n; i++) {
		NodeList2[i] = new HuffmanNode<T, E>;
	}

	int i;
	for (i = 0; i < n - 1; i++) {
		hp.removeMin(first);			// 选择根权值最小的树
		hp.removeMin(second);			// 选择根权值次小的树
		mergeTree(first, second, NodeList2[i]);	// 合并树
		hp.Insert(NodeList2[i]);				// 重新插入最小堆中
										// 具体过程详见数据结构书P255(Edge页码)
	}
	this->root = NodeList2[i - 1];			// 建立根结点
}

template<class T, class E>
void HuffmanTree<T, E>::mergeTree(HuffmanNode<T, E> * ht1,
	HuffmanNode<T, E> * ht2,
	HuffmanNode<T, E> * parent) {
	
	parent->leftChild = ht1;
	parent->rightChild = ht2;

	parent->data = ht1->data + ht2->data;
	
	ht1->parent = parent;
	ht2->parent = parent;
}

template<class T, class E>
void HuffmanTree<T, E>::traverse() {
	this->Traverse(this->root);
}

template<class T, class E>
void HuffmanTree<T, E>::Traverse(HuffmanNode<T, E> * tree) {
	if (tree != NULL) {
		cout << "data : " << tree->data << endl;
		this->Traverse(tree->leftChild);
		this->Traverse(tree->rightChild);
	}
}

#endif // __H_M__
