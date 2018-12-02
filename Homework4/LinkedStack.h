// LinkedStack.h

# ifndef __LS_H__
# define __LS_H__

# include<iostream>
# include"LinkNode.h"

using namespace std;

template<class T>
class LinkedStack{
public:
	LinkedStack();
	~LinkedStack();

	void Push(const T &x);	// 新元素进栈
	bool Pop(T &x, int &i);	// 弹出栈

	bool getTop(T &x) const;	// 读取栈顶元素，由x返回

	void makeEmpty();	// 清空栈内容

	bool IsEmpty() const;
	bool IsFull() const;

	int getSize() const;

	void PrintLinkedStack();
private:
	LinkNode<T> * top;

	int size;

	friend ostream & operator<< <>(ostream &os, LinkedStack<T> &s);
};

template<class T>
LinkedStack<T>::LinkedStack() {	// 构造函数，置空栈
	this->top = new LinkNode<T>(NULL, NULL);

	this->size = 0;
}

template<class T>
void LinkedStack<T>::makeEmpty() {
	// 声明工作指针
	LinkNode<T> * p;

	while (this->top != NULL) {
		p = this->top;
		top = top->link;
		delete p;
	}

	this->size = 0;
}

template<class T>
bool LinkedStack<T>::Pop(T &x, int &i) {
	// 声明工作指针
	LinkNode<T> * p;

	i = this->getSize();

	if (this->IsEmpty() == false) {
		p = this->top;
		this->top = this->top->link;

		x = p->data;

		cout<< "Pop("<< x<< ")"<< endl;
		delete p;

		--this->size;
		i = this->getSize();

		return true;
	} else {
		return false;
	}
}

template<class T>
bool LinkedStack<T>::getTop(T &x) const {
	if (this->IsEmpty() == false) {
		x = this->top->data;
		cout<< "getTop("<< x<< ")"<< endl;

		return true;
	} else {
		return false;
	}
}

template<class T>
LinkedStack<T>::~LinkedStack() {
	// 析构函数
	this->makeEmpty();
}

template<class T>
void LinkedStack<T>::Push(const T &x) {
	// 创建新节点，通过LinkNode的构造函数
	 // 并将旧节点（top）作为新节点（top）的link

	// 声明工作指针p，暂存this->top
	LinkNode<T> * p = this->top;

	// 新的top连上先前的top
	this->top = new LinkNode<T>(x, p);
	
	// 断言，分配空间是否成功
	//assert(this->top != NULL);

	++this->size;
	cout<< "Operate: Push("<< x<< ")"<< endl;
}

template<class T>
bool LinkedStack<T>::IsEmpty() const {
	return (this->top == NULL) ? true : false;
}

template<class T>
bool LinkedStack<T>::IsFull() const {
	return false;	// Never being Full ! 
}

template<class T>
int LinkedStack<T>::getSize() const {
	return this->size;
}

template<class T>
ostream & operator<<(ostream &os, LinkedStack<T> &s) {
	// 输出栈中元素的重载操作<<
	os<< "栈中的元素："<< s.getSize()<< endl;
	
	// 声明工作指针
	LinkNode<T> * p = s.top;
	
	// 声明计数器
	int i = 0;

	while (p != NULL) {
		os<< ++i<< ":"<< p->data<< endl;
		p = p->link;
	}

	return os;
}

template<class T>
void LinkedStack<T>::PrintLinkedStack() {
	// 声明工作指针
	LinkNode<T> * p = this->top;

	cout<< "Start to print the Stack : "<< endl;

	int count = 0;

	while (p->data != NULL) {
		count += 1;
		cout<< "这是第"<< count<< "个元素 : "<< p->data<< endl;

		p = p->link;
	}
}

# endif
