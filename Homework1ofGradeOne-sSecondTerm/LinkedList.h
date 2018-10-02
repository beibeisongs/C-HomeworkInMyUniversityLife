// LinkedList.h

# ifndef __L_H__
# define __L_H__

# include"LinkNode.h"
# include<string>
# include<iostream>

using namespace std;

class LinkedList {
public:
	LinkedList();

	LinkNode<int> * getHead();
	LinkNode<int> * getLast();
	int getLength();

	void insert(const int &x);

	bool isEmpty();
	void makeEmpty();

	void printList();
	void printNumber();
	
private:

	LinkNode<int> * first;
	LinkNode<int> * last;

	int length;
};

# endif