// LinkedList.cpp

# include<iostream>
# include"LinkedList.h"
# include"LinkNode.h"
# include<string>

using namespace std;

LinkedList::LinkedList() {
	
	this->first = new LinkNode<int>(NULL, NULL);
	this->last = new LinkNode<int>(NULL, NULL);
	
	first->link = this->last;

	this->length = 0;
}

LinkNode<int> * LinkedList::getHead() {
	return this->first;
}

LinkNode<int> * LinkedList::getLast() {
	return this->last;
}

int LinkedList::getLength() {
	return length;
}

void LinkedList::insert(const int &x) {

	// Create a new Node
	LinkNode<int> * p = new LinkNode<int>(NULL, NULL);

	// Declare a working pointer to restore the value of this->last temporarily
	LinkNode<int> * last = this->getLast();
	last->link = p;
	last->data = x;

	this->last = p;

	/*Attention:
		So my class LinkedList 's pointer first
		Normally has its own data

		Becase I use the operation:
		last = this->getHead()
		 at the Construstor Function
	*/
	this->length += 1;
}

bool LinkedList::isEmpty() {
	return (length == 0);
}

void LinkedList::makeEmpty() {
	if (! this->isEmpty()) {

		LinkNode<int> * p = this->getHead()->link;

		LinkNode<int> * temp;
	
		 while (p->link != NULL) {

			p->data = NULL;

			temp = p;

			p = p->link;

			delete temp;

			this->length -= 1;

		 }

		 this->last = new LinkNode<int>(NULL, NULL);
	
		 first->link = this->last;

		 this->length = 0;
	}
}

void LinkedList::printList() {

	LinkNode<int> * p = this->getHead()->link;

	/*Attention:
		So my class LinkedList 's pointer first
		Normally has its own data

		Becase I use the operation:
		last = this->getHead()
		 at the Construstor Function
	*/

	cout<< "List 's data : "<< endl;
	while (p->link != NULL) {
		cout<< p->data<< endl;
		p = p->link;
	}
}

void LinkedList::printNumber() {

	LinkNode<int> * p = this->getHead()->link;

	int nums_len = this->getLength() * 3;
	int * nums = new int[nums_len];

	/*Attention:
		So my class LinkedList 's pointer first
		Normally has its own data

		Becase I use the operation:
		last = this->getHead()
		 at the Construstor Function
	*/

	int num_i = 0;

	while (p->link != NULL) {
		if (p->data < 10) {
			nums[num_i] = p->data;
			
			nums[++num_i] = 0;
			
			nums[++num_i] = 0;
			
		} else {
			if (p->data < 100) {
				nums[num_i] = p->data;
				
				nums[++num_i] = 0;
				
			} else {
				nums[num_i] = p->data;
				
			}
		}
		
		num_i += 1;

		p = p->link;
	}
	
	bool mark_show = true;

	cout<< "List 's data : ";
	for (int i = num_i - 1; i >= 0; i --) {
		if (mark_show) {
			if (nums[i] != 0) {
				cout<< nums[i];
				mark_show = false;
			}
		} else {
			cout<< nums[i];
		}
	} cout<< endl;
	cout<< endl;

	delete[] nums;
}