// LinkedStack.h

# ifndef __LS_H__
# define __LS_H__

# include<iostream>
# include<string>
# include"LinkNode.h"

using namespace std;

class LinkedStack {
public:
	LinkedStack();
	~LinkedStack();

	void Push(const string &x);	// 新元素进栈
	bool Pop(string &x, int &i);	// 弹出栈

	bool getTop(string &x) const;	// 读取栈顶元素，由x返回

	void makeEmpty();	// 清空栈内容

	bool IsEmpty() const;
	bool IsFull() const;

	int getSize() const;

	void PrintLinkedStack();
private:
	LinkNode<string> * top;

	int size;

	friend ostream & operator<< (ostream &os, LinkedStack &s);
};

LinkedStack::LinkedStack() {	// 构造函数，置空栈
	this->top = new LinkNode<string>("", NULL);

	this->size = 0;
}

void LinkedStack::makeEmpty() {
	// 声明工作指针
	LinkNode<string> * p;

	while (this->top != NULL) {
		p = this->top;
		top = top->link;
		delete p;
	}

	this->size = 0;
}

bool LinkedStack::Pop(string &x, int &i) {
	// 声明工作指针
	LinkNode<string> * p;

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

bool LinkedStack::getTop(string &x) const {
	if (this->IsEmpty() == false) {
		x = this->top->data;
		cout<< "getTop("<< x<< ")"<< endl;

		return true;
	} else {
		return false;
	}
}

LinkedStack::~LinkedStack() {
	// 析构函数
	this->makeEmpty();
}

void LinkedStack::Push(const string &x) {
	// 创建新节点，通过LinkNode的构造函数
	 // 并将旧节点（top）作为新节点（top）的link

	// 声明工作指针p，暂存this->top
	LinkNode<string> * p = this->top;

	this->top = new LinkNode<string>(x, p);
	
	// 断言，分配空间是否成功
	//assert(this->top != NULL);

	++this->size;
	cout<< "Operate: Push("<< x<< ")"<< endl;
}

bool LinkedStack::IsEmpty() const {
	return (this->top == NULL) ? true : false;
}

bool LinkedStack::IsFull() const {
	return false;	// Never being Full ! 
}

int LinkedStack::getSize() const {
	return this->size;
}

ostream & operator<<(ostream &os, LinkedStack &s) {
	// 输出栈中元素的重载操作<<
	os<< "栈中的元素："<< s.getSize()<< endl;
	
	// 声明工作指针
	LinkNode<string> * p = s.top;
	
	// 声明计数器
	int i = 0;

	while (p != NULL) {
		os<< ++i<< ":"<< p->data<< endl;
		p = p->link;
	}

	return os;
}

void LinkedStack::PrintLinkedStack() {
	// 声明工作指针
	LinkNode<string> * p = this->top;

	cout<< "Start to print the Stack : "<< endl;

	int count = 0;

	while (p->data != "") {
		count += 1;
		cout<< "这是第"<< count<< "个元素 : "<< p->data<< endl;

		p = p->link;
	}
}

# endif