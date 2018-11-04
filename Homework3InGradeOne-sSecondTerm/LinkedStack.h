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

	void Push(const T &x);	// ��Ԫ�ؽ�ջ
	bool Pop(T &x, int &i);	// ����ջ

	bool getTop(T &x) const;	// ��ȡջ��Ԫ�أ���x����

	void makeEmpty();	// ���ջ����

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
LinkedStack<T>::LinkedStack() {	// ���캯�����ÿ�ջ
	this->top = new LinkNode<T>(NULL, NULL);

	this->size = 0;
}

template<class T>
void LinkedStack<T>::makeEmpty() {
	// ��������ָ��
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
	// ��������ָ��
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
	// ��������
	this->makeEmpty();
}

template<class T>
void LinkedStack<T>::Push(const T &x) {
	// �����½ڵ㣬ͨ��LinkNode�Ĺ��캯��
	 // �����ɽڵ㣨top����Ϊ�½ڵ㣨top����link

	// ��������ָ��p���ݴ�this->top
	LinkNode<T> * p = this->top;

	// �µ�top������ǰ��top
	this->top = new LinkNode<T>(x, p);
	
	// ���ԣ�����ռ��Ƿ�ɹ�
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
	// ���ջ��Ԫ�ص����ز���<<
	os<< "ջ�е�Ԫ�أ�"<< s.getSize()<< endl;
	
	// ��������ָ��
	LinkNode<T> * p = s.top;
	
	// ����������
	int i = 0;

	while (p != NULL) {
		os<< ++i<< ":"<< p->data<< endl;
		p = p->link;
	}

	return os;
}

template<class T>
void LinkedStack<T>::PrintLinkedStack() {
	// ��������ָ��
	LinkNode<T> * p = this->top;

	cout<< "Start to print the Stack : "<< endl;

	int count = 0;

	while (p->data != NULL) {
		count += 1;
		cout<< "���ǵ�"<< count<< "��Ԫ�� : "<< p->data<< endl;

		p = p->link;
	}
}

# endif