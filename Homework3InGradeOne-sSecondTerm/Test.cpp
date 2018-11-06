// Test.cpp

# include<iostream>
# include"BinaryTree.h"
# include"LinkedStack.h"

using namespace std;

int main() {

	BinaryTree<int> * tree = new BinaryTree<int>;
	cout<< "Now start creating a binary tree !"<< endl;
	cin>> tree;

	
	// Test the Find Function
	// LinkedStack<BinTreeNode<int> *> * ans = new LinkedStack<BinTreeNode<int> *>;
	// ans = tree->Find(3);

	// Test the SwapTree Function
	BinTreeNode<int> * newTree = new BinTreeNode<int>;
	newTree = tree->SwapTree(tree->getRoot());

	
	cout<< "Please input the mark value: "<< endl;
	int mark;
	cin>> mark;

	return 0;
}