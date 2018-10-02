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

	void Push(const string &x);	// ��Ԫ�ؽ�ջ
	bool Pop(string &x, int &i);	// ����ջ

	bool getTop(string &x) const;	// ��ȡջ��Ԫ�أ���x����

	void makeEmpty();	// ���ջ����

	bool IsEmpty() const;
	bool IsFull() const;

	int getSize() const;

	void PrintLinkedStack();
private:
	LinkNode<string> * top;

	int size;

	friend ostream & operator<< (ostream &os, LinkedStack &s);
};

LinkedStack::LinkedStack() {	// ���캯�����ÿ�ջ
	this->top = new LinkNode<string>("", NULL);

	this->size = 0;
}

void LinkedStack::makeEmpty() {
	// ��������ָ��
	LinkNode<string> * p;

	while (this->top != NULL) {
		p = this->top;
		top = top->link;
		delete p;
	}

	this->size = 0;
}

bool LinkedStack::Pop(string &x, int &i) {
	// ��������ָ��
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
	// ��������
	this->makeEmpty();
}

void LinkedStack::Push(const string &x) {
	// �����½ڵ㣬ͨ��LinkNode�Ĺ��캯��
	 // �����ɽڵ㣨top����Ϊ�½ڵ㣨top����link

	// ��������ָ��p���ݴ�this->top
	LinkNode<string> * p = this->top;

	this->top = new LinkNode<string>(x, p);
	
	// ���ԣ�����ռ��Ƿ�ɹ�
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
	// ���ջ��Ԫ�ص����ز���<<
	os<< "ջ�е�Ԫ�أ�"<< s.getSize()<< endl;
	
	// ��������ָ��
	LinkNode<string> * p = s.top;
	
	// ����������
	int i = 0;

	while (p != NULL) {
		os<< ++i<< ":"<< p->data<< endl;
		p = p->link;
	}

	return os;
}

void LinkedStack::PrintLinkedStack() {
	// ��������ָ��
	LinkNode<string> * p = this->top;

	cout<< "Start to print the Stack : "<< endl;

	int count = 0;

	while (p->data != "") {
		count += 1;
		cout<< "���ǵ�"<< count<< "��Ԫ�� : "<< p->data<< endl;

		p = p->link;
	}
}

# endif