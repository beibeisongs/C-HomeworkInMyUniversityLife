// LinkedQueue.h

# ifndef __CQ_H__
# define __CQ_H__

# include<iostream>

using namespace std;

template<class T>
class LinkedQueue;	// Declare the class Queue in advance
					// Because class LinkedNode use it as friend class

template<class T>
class LinkedNode {
	friend class LinkedQueue<T>;
private:
	T data;
	LinkedNode<T> * next;
};

template<class T>
class LinkedQueue {
public:
	LinkedQueue();
	~LinkedQueue();

	bool isEmpty();
	void makeEmpty();

	bool EnQueue(const T &x);
	bool DeQueue(T &x);

	bool getFront(T &x) const;
	int getSize() const;

private:
	friend ostream & operator<< (ostream &os, LinkedQueue<T> &Q);

	LinkedNode<T> * front;
	LinkedNode<T> * rear;
};

template<class T>
LinkedQueue<T>::LinkedQueue() {
	this->front = NULL;
	this->rear = NULL;
}

template<class T>
LinkedQueue<T>::~LinkedQueue() {
	this->makeEmpty();
}

template<class T>
bool LinkedQueue<T>::isEmpty() {
	return this->front == NULL;
}

template<class T>
void LinkedQueue<T>::makeEmpty() {
	// Declare a job variable to restore the current position
	LinkedNode<T> * ptr = this->front;

	LinkedNode<T> * temp = ptr;
	while (ptr != NULL) {
		ptr->data = NULL;
		ptr = ptr->next;

		delete temp;
	}

	this->front = this->rear = NULL;
}

template<class T>
bool LinkedQueue<T>::EnQueue(const T &x) {

	LinkedNode<T> * p = new LinkedNode<T>();
	p->data = x;
	p->next = NULL;

	if (p == NULL) {
		return false;
	}
	//cout << x << " enter Queue ! " << endl;


	if (this->isEmpty()) {
		this->front = this->rear = p;
	}
	else {
		this->rear->next = p;
		this->rear = this->rear->next;
	}

	return true;
}

template<class T>
bool LinkedQueue<T>::DeQueue(T &x) {
	if (this->isEmpty() == true) {
		cout << "Error : already empty ! " << endl;

		return false;
	}

	LinkedNode<T> * p = this->front;
	x = p->data;
	//cout << "Pop : " << x << endl;

	this->front = this->front->next;
	delete p;

	return true;
}

template<class T>
bool LinkedQueue<T>::getFront(T &x) const {
	if (this->isEmpty() == true) {
		return false;
	}

	x = this->front->data;
	return true;
}

template<class T>
int LinkedQueue<T>::getSize() const {
	LinkedNode<T> * p = this->front;

	int i = 0;
	while (p != NULL) {
		i += 1;

		p = p->next;
	}

	return i;
}

template<class T>
ostream & operator<<(ostream &os, LinkedQueue<T> &Q) {
	os << "The size of the CircularQueue is : " << Q.getSize() << endl;

	LinkedNode<T> * p = Q.front;

	int i = 0;
	while (p != NULL) {
		os << ++i << " : " << p->data << endl;
		p = p->next;
	}

	return os;
}

# endif