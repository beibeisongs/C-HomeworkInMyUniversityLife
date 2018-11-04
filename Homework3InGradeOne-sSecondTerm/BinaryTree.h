// BinaryTree.h

# ifndef __BT_H__
# define __BT_H__

# include<iostream>
# include"LinkedQueue.h"
# include"LinkedStack.h"

using namespace std;

template<class T>
struct BinTreeNode {
	T data;

	BinTreeNode<T> * leftChild;
	BinTreeNode<T> * rightChild;

	BinTreeNode();	// Constructor

	BinTreeNode(T x);
};

template<class T>
BinTreeNode<T>::BinTreeNode() {
	this->leftChild = NULL;
	this->rightChild = NULL;
}

template<class T>
BinTreeNode<T>::BinTreeNode(T x) {
	this->data = x;
	this->leftChild = NULL;
	this->rightChild = NULL;
}

template<class T>
class BinaryTree {
public:
	BinaryTree();	// Constructor
	BinaryTree(T value);
	BinaryTree(BinaryTree<T> &s);	// Copy Constructor
	~BinaryTree() {
		this->destroy(this->root);
	}

	bool IsEmpty() {
		return (this->root == NULL ? true : false;);
	}

	BinTreeNode<T> * Parent(BinTreeNode<T> * current) {	// return the parent of the current
		return (root == NULL || root == current)? NULL : this->parent(this->root, current);
	}
	BinTreeNode<T> * LeftChild(BinTreeNode<T> * current) {
		return (current != NULL) ? current->leftChild : NULL;
	}
	BinTreeNode<T> * RightChild(BinTreeNode<T> * current) {
		return (current != NULL) ? current->rightChild : NULL;
	}

	int Height() const {
		return this->height(this->root);
	}
	int Size() const {
		return this->size(this->root);
	}

	BinTreeNode<T> * getRoot() const {
		return this->root;
	}

	void PreOrder(void (* visit) (BinTreeNode<T> * p)) {
		this->preOrder(this->root, visit);
	}
	void InOrder(void (* visit) (BinTreeNode<T> * p)) {
		this->inOrder(this->root, visit);
	}
	void PostOrder(void (* visit) (BinTreeNode<T> * p)) {
		this->postOrder(this->root, visit);
	}
	void LevelOrder(BinTreeNode<T> * p);

	LinkedStack<BinTreeNode<T> *> * Find(T item);
protected:
	bool find(LinkedStack<BinTreeNode<T> *> * ans, T item, BinTreeNode<T> * subTree);

	BinTreeNode<T> * root;
	T RefValue;	// Data Inputing Stoping Signal

	void CreateBinTree(BinTreeNode<T> * subTree);

	BinTreeNode<T> * parent(BinTreeNode<T> * subTree, BinTreeNode<T> * current);	// return the parent Node
	
	int height(BinTreeNode<T> * subTree) const;	// return the depth of the tree
	int size(BinTreeNode<T> * subTree) const;	// return the num of the tree-nodes

	void Traverse(BinTreeNode<T> * subTree, ostream &out);	// preOrder output
	void preOrder(BinTreeNode<T> &subTree, 
					void (* visit) (BinTreeNode<T> * p));	// preOrder Traverse
	void inOrder(BinTreeNode<T> * subTree, 
					void (* visit) (BinTreeNode<T> * p));	// inOrder Traverse
	void postOrder(BinTreeNode<T> &Tree, 
					void (* visit) (BinTreeNode<T> * p));	// postOrder Traverse
	
	void destroy(BinTreeNode<T> * &subTree);

	BinTreeNode<T> * Copy(BinTreeNode<T> * orinode);	// return the target tree node
	
	friend istream & operator >> <>(istream &in, BinaryTree<T> * Tree);
	friend ostream & operator << <>(ostream &out, BinaryTree<T> &Tree);
};

template<class T>
BinaryTree<T>::BinaryTree() {
	this->root = NULL;
	// Attention: 
	//	there is no operation to initialize the RefValue
	//		and you can know from your debugging experience that
	//		RefValue will be initialized automatically by a minus number
}

template<class T>
BinaryTree<T>::BinaryTree(T value) {
	this->RefValue = value;
	this->root = NULL;
}

template<class T>
BinaryTree<T>::BinaryTree(BinaryTree<T> &s) {
	this->root = this->Copy(s.root);
}

template<class T>
BinTreeNode<T> * BinaryTree<T>::parent(BinTreeNode<T> * subTree, BinTreeNode<T> * current) {
	// protected function, search for the parent node of the current
	// when found the parent of the current, return its location, else return NULL
	if (subTree == NULL) {
		return NULL;
	}

	if (subTree->leftChild == current || subTree->rightChild == current) {
		return subTree;
	}

	// declare a job variable
	BinTreeNode<T> * p;
	if ((p = this->parent(subTree->leftChild, current)) != NULL) {
		return p;	// recursion search
	} else {
		return this->parent(subTree->rightChild, current);	// recursion search
	}
}

template<class T>
int BinaryTree<T>::height(BinTreeNode<T> * subTree) const {
	// protected function : calculate the height of the tree with * subTree as its root
	if (subTree == NULL) {
		return 0;
	} else {
		int i = this->height(subTree->leftChild);
		int j = this->height(subTree->rightChild);

		return (i < j) ? j + 1 : i + 1;
	}
}

template<class T>
int BinaryTree<T>::size(BinTreeNode<T> * subTree) const {
	// protected function: calculate the num of the sumTree-nodes
	if (subTree == NULL) {
		return 0;	// stop the recursion process
	} else {
		return 1 + this->size(subTree->leftChild) + this->size(subTree->rightChild);
	}
}

template<class T>
void BinaryTree<T>::preOrder(BinTreeNode<T> &subTree, 
					void (* visit) (BinTreeNode<T> * p)) {	// preOrder Traverse
	if (subTree != NULL) {
		visit(subTree);	// visit the root-node
		this->preOrder(subTree->leftChild, visit);	// preOrder Traverse the left Child
		this->preOrder(subTree->rightChild, visit);	// preOrder Traverse the right Child
	}
}

template<class T>
void BinaryTree<T>::inOrder(BinTreeNode<T> * subTree, 
	void (* visit) (BinTreeNode<T> * p)) {	// inOrder Traverse
	
		if (subTree != NULL) {
			this->inOrder(subTree->leftChild, visit);
			visit(subTree);
			this->inOrder(subTree->rightChild, visit);
		}
}

template<class T>
void BinaryTree<T>::postOrder(BinTreeNode<T> &subTree, 
	void (* visit) (BinTreeNode<T> * p)) {	// postOrder Traverse
	
		if (subTree != NULL) {	// The stoping signal for recursion
			this->postOrder(subTree->leftChild, visit);
			this->postOrder(subTree->rightChild, visit);
			visit(subTree);
		}
}

template<class T>
void BinaryTree<T>::LevelOrder(BinTreeNode<T> * p) {
	LinkedQueue<BinTreeNode<T> *> Q;

	p = this->root;

	Q.EnQueue(p);
	while (! Q.isEmpty()) {
		Q.DeQueue(p);
		cout<< p->data<< " ";

		if (p->leftChild != NULL) {
			Q.EnQueue(p->leftChild);	// leftChild enters the Queue
		}
		if (p->rightChild != NULL) {
			Q.EnQueue(p->rightChild);	// rightChild enters the Queue
		}
	}
}

template<class T>
BinTreeNode<T> * BinaryTree<T>::Copy(BinTreeNode<T> * orinode) {
	// protected function: returning a pointer of the target tree
	if (orinode == NULL) {
		return NULL;
	}
	BinTreeNode<T> * temp = new BinTreeNode<T>;	// create a root node(pointer)
	temp->data = orinode->data;
	temp->leftChild = this->Copy(orinode->leftChild);
	temp->rightChild = this->Copy(orinode->rightChild);
	
	return temp;	// pointer temp stands for the root node of the target tree
}

template<class T>
void BinaryTree<T>::destroy(BinTreeNode<T> * &subTree) {
	// protected function: delete the subTree when the pointer is not null
	if (subTree != NULL) {
		this->destroy(subTree->leftChild);
		this->destroy(subTree->rightChild);
		delete subTree;
	}
}

template<class T>
void BinaryTree<T>::CreateBinTree(BinTreeNode<T> * subTree) {
	// protected function: create binary tree
	T item;

	char m;
	
	cout<< "Now input the new item : "<< endl;
	cin>> item;
	cout<< item<< " was input ! "<< endl;

	if (item != this->RefValue) {
		
		subTree->data = item;
		cout<< "subTree : "<< subTree<< endl;
		cout<< "subTree->data : "<< subTree->data<< endl;

		cout<< endl;
		cout<< "This is the temporary tree (level order output) : "<< endl;
		this->LevelOrder(this->root);
		cout<< endl;

		// The operation to exit the creating process
		cout<< "If you want to input its left child ? Please input the mark: "<< endl;
		cin>> m;
		if (m != '#') {
			subTree->leftChild = new BinTreeNode<T>;
			this->CreateBinTree(subTree->leftChild);
		}	

		// The operation to exit the creating process
		cout<< "If you want to input its right child ? Please input the mark: "<< endl;
		cin>> m;
		if (m != '#') {
			subTree->rightChild = new BinTreeNode<T>;
			this->CreateBinTree(subTree->rightChild);
		}

	} else {
		subTree = NULL;	// Make this pointer empty
	}

}

template<class T>
void BinaryTree<T>::Traverse(BinTreeNode<T> * subTree, ostream &out) {
	// Protected function: 
	//		Search and output the BinaryTree, whose root is subTree(the parameter)
	if (subTree != NULL) {
		out<< subTree->data<< ' ';
		this->Traverse(subTree->leftChild, out);
		this->Traverse(subTree->rightChild, out);
	}
	out<< endl;
}

template<class T>
istream & operator >> (istream &in, BinaryTree<T> * Tree) {
	// reloading operation: 
	//		Input and create a BinaryTree
	cout<< "Now let's start creating a binary tree "<< endl;
	cout<< "Please do as the tips say"<< endl;
	cout << "please input some numbers:" << endl;
	cout<< "Attention: input the number one by one, and the binary tree will be created by PreOrder operation "<< endl;

	Tree->root = new BinTreeNode<T>;
	cout<< "Tree.root : "<< Tree->root<< endl;

	Tree->CreateBinTree(Tree->root);
	
	return in;
}

template<class T>
ostream & operator <<(ostream &out, BinaryTree<T> &Tree) {
	//  reloading operation: 
	//		output a tree
	Tree.Traverse(Tree.root, out);
	out<< endl;

	return out;
}

template<class T>
LinkedStack<BinTreeNode<T> *> * BinaryTree<T>::Find(T item) {
	BinTreeNode<T> * p = this->root;

	LinkedStack<BinTreeNode<T> *> * ans;

	BinTreeNode<T> * trash;
	int i;

	bool flag = false;

	if (p != NULL) {
		
		if (p->data == item) {
			return ans;
		} else {

			ans->Push(p);
			flag = this->find(ans, item, p->leftChild);
			if (flag) {
				return ans;

			} else {
				ans->Pop(trash, i);	
			}

			ans->Push(p);
			flag = this->find(ans, item, p->rightChild);
			if (flag) {
				return ans;

			} else {
				ans->Pop(trash, i);	
				
				return ans;
			}

		}

	} else {
		return ans;
	}

}

template<class T>
bool BinaryTree<T>::find(LinkedStack<BinTreeNode<T> *> * ans, T item, BinTreeNode<T> * subTree) {
	
	bool flag = false;

	BinTreeNode<T> * trash;
	
	if (subTree != NULL) {
		
		if (subTree->data == item) {
			return true;
		} else {
			ans->Push(subTree);
			flag = this->find(ans, item, subTree->leftChild);
			if (flag) {
				return true;

			} else {
				ans->Pop(trash, i);	
			}

			ans->Push(subTree);
			flag = this->find(ans, item, subTree->rightChild, temp_temp_t);
			if (flag) {
				return true;

			} else {
				ans->Pop(trash, i);

				return false;
			}

		}
	} else {
		return false;
	}
}

# endif