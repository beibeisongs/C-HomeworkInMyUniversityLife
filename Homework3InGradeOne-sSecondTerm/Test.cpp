// Test.cpp

# include<iostream>
# include"BinaryTree.h"
# include"LinkedStack.h"
# include<vector>

using namespace std;

int main() {

	// 功能测试：前序中序确定二叉树
	BinaryTree<int> * t1 = new BinaryTree<int>;
	BinTreeNode<int> * t2 = new BinTreeNode<int>;
	
	int arr[7] = {1, 2, 3, 4};
	vector<int> pre(arr, arr + 4); //从数组中获得初值

	int arr2[7] = {2, 1, 4, 3};
	vector<int> in(arr2, arr2 + 4); //从数组中获得初值

	t2 = t1->reBuildBinaryTree(pre, in);

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
