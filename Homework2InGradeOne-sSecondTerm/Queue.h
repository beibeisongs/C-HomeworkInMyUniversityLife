// LinkedQueue.h

# ifndef __L_Q_H__
# define __L_Q_H__
 
# include<iostream>
# include<string>

using namespace std;

class Queue;	// Declare the class Queue in advance
				 // Because class LinkedNode use it as friend class

class LinkedNode {
public:
	friend class Queue;

	string data;
	LinkedNode * next;
};

class Queue {
public:
	Queue() {
		this->front = this->rear = 0;
		this->length = 0;
	}

	int Length();
	
	bool isEmpty();

	void Front();
	LinkedNode * getFront();
	void Rear();
	char * toCharList();

	void Push(string item);
	string Pop();

	void print();
private:
	LinkedNode * front;
	LinkedNode * rear;

	int length;
};

bool Queue::isEmpty() {
	return front == 0;
}

int Queue::Length() {
	int length = this->length;
	return length;
}


void Queue::Front() {
	if (!this->isEmpty()) {
		cout<< "The front data is : "<< this->front->data<<endl;
	} else {
		cout<< "Error : the Queue is empty ! "<< endl;
	}
}


LinkedNode * Queue::getFront() {
	return this->front;
}

void Queue::Rear() {
	if (! this->isEmpty()) {
		cout<< "The rear data is : "<< this->rear->data<< endl;
	} else {
		cout<< "Error : the Queue is empty ! "<< endl;
	}

}

void Queue::Push(string item) {
	LinkedNode * p = new LinkedNode();

	p->data = item;
	p->next = NULL;

	cout<< item<< " enter Queue ! "<< endl;

	this->length += 1;

	if (this->isEmpty()) {
		this->front = this->rear = p;
	} else {
		this->rear->next = p;
		this->rear = p;
	}
}

string Queue::Pop() {
	string data;	// Declare a job varivable to restore the popped data

	if (this->isEmpty()) {
		cout<< "Error : the Queue is Empty, can't delete any ! "<< endl;
	} else {

		this->length -= 1;

		LinkedNode * p = this->front;
		
		cout<< front->data<< "drop out of the Queue ! "<< endl;
		data = front->data;

		this->front = this->front->next;

		delete p;

		return data;
	}
}

void Queue::print() {
	// Declare a job variable to restore the current position
	LinkedNode * ptr = this->front;

	while (ptr != NULL) {
		cout<< "The value is : "<< ptr->data<< endl;
		ptr = ptr->next;
	}
}

# endif