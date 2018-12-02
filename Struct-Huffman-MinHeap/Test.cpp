// Test.cpp

#include<iostream>
#include"Heap.h"
#include"HuffmanTree.h"

using namespace std;

int main() {

	int arr[4];
	arr[0] = 3;
	arr[1] = 2;
	arr[2] = 1;
	arr[3] = 0;
	HuffmanTree<int, int> hft1(arr, 4);
	hft1.traverse();

	cout << "Please input the mark you like : " << endl;
	int mark;
	cin >> mark;

	return 0;
}
