// Test.cpp

# include<iostream>
# include"BinaryTree.h"

using namespace std;

int main() {

	BinaryTree<int> * tree = new BinaryTree<int>;
	cout<< "Now start creating a binary tree !"<< endl;
	cin>> tree;

	
	cout<< "Please input the mark value: "<< endl;
	int mark;
	cin>> mark;

	return 0;
}