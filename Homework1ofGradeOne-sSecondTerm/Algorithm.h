// Algorithm.h

# ifndef __A_H__
# define __A_H__

# include"LinkNode.h"
# include"LinkedList.h"
# include<iostream>
# include<string>

using namespace std;

class Algorithm {
public:
	Algorithm() { }
	
	void factorial(int x);
	
	LinkedList * constructList(string x);
	
	LinkedList * LinkedListMultiplied_K(int k, LinkedList * l1);

	LinkedList * LinkedListsSum(LinkedList **l2, int m_len);
	
	void reSizeLinkedLists(LinkedList **l2, int m_len, int m_len_before);

	LinkedList * Multiply(string x_str, int m);

	string list2String(LinkedList * l1);
};

# endif