// Algorithm.cpp

# include<iostream>
# include<string>
# include<string.h>
# include"LinkNode.h"
# include"LinkedList.h"
# include"Algorithm.h"
# include<cmath>

using namespace std;

LinkedList * Algorithm::constructList(string x) {
	/*The first part:
		get the length of the x
	*/
	int x_len = x.length();

	/*
		Declare the working variable
		 to record the position pointing at 
		  the number n
	*/
	int num_i = 0;

	/*
		Declare the working variable
		 responsible for the construction of
		  the LinkNode 's data
	*/
	int p_sum = 0;

	/*
		Declare the working LinkedList-1
		 to restore the original data of x

		Becase the length of the x is uncertain
	*/
	LinkedList * l1 = new LinkedList;

	for (int i = x_len - 1; i >= 0; i --) {
		num_i += 1;

		switch (num_i) {
		case 1:
			p_sum += (int)(x[i] - 48);
			break;
		case 2:
			p_sum += ((int)(x[i] - 48)) * 10;
			break;
		case 3:
			p_sum += ((int)(x[i] - 48)) * 100;
			break;
		}

		if (num_i == 3) {

			if (p_sum >= 0) {
				l1->insert(p_sum);
			}

			num_i = 0;

			p_sum = 0;
		}
	}

	if (p_sum > 0) {
		l1->insert(p_sum);
	}

	return l1;
}

LinkedList * Algorithm::Multiply(string x_str, int m) {

	LinkedList * l1  = this->constructList(x_str);

	/*Attention:
		The order following 
			shows the usage of the function constructList

		>>>LinkedList l1 = this->constructList(str);
	*/

	string m_str = to_string((long long)m);

	int m_len = m_str.length();

	LinkedList ** l2 = new LinkedList * [m_len];

	/*
			variable k restore each part of the multiplied number m_str
		*/
	int k = 0;

	for (int i = m_len - 1; i >= 0; i --) {
			
		k = (int)(m_str[i] - 48);

		l2[m_len - 1 - i] = this->LinkedListMultiplied_K(k, l1);
	}

	l1->makeEmpty();
	l1 = this->LinkedListsSum(l2, m_len);

	/*
		Retrive the memory of **l2,
	*/
	for (int i = 0; i < m_len; i ++) {
		l2[i]->makeEmpty();

		delete l2[i];
	}
	delete[] l2;

	return l1;
}

LinkedList * Algorithm::LinkedListMultiplied_K(int k, LinkedList * l1) {
	/*Desciption:

		k is the single part of the Multiplied Num
		 and the k_evil is the time-recording assistance variable like 100 
		  refering to the position of k related to the original Multiplied Number
	*/
	
	/*
		Create a new LinkedList l2
		 to Restore the middle result of the Multiplying Process
	*/
	LinkedList * l2 = new LinkedList;

	/*
		Declare a working pointer for the l1
	*/
	LinkNode<int> * ptr1 = l1->getHead()->link;

	/*
		Declare the variable v_d to restore
	*/
	int v_d = 0;
	while (ptr1->link != NULL) {
		/*
			Declare a variable to restore the value
			 of the result of the multiplied node's data
		*/
		int v_e = ptr1->data * k;

		/*
			Declare the variable v_m to restore the result of
			 the v_e moded by 1000
		
			Then add it to the next node 's data
		*/
		int v_m = v_e % 1000 + v_d;
		/*
			Insert the new result to the l2
		*/
		l2->insert(v_m);

		v_d = (v_e + v_d - v_m) / 1000;

		ptr1 = ptr1->link;

	}

	if (v_d != 0) {
		l2->insert(v_d);
	}

	return l2;
}

LinkedList * Algorithm::LinkedListsSum(LinkedList **l2, int m_len) {
	/*
		sum_len = (l2->getLength() * 3) + m_len

		Becase every LinkNode has 3 int elements
	*/
	int sum_len = (l2[m_len - 1]->getLength() * 3) + m_len - 1;
	int * sum = new int[sum_len];
	/*
		Initialize the array-sum
	*/
	for (int i = 0; i < sum_len; i ++) {
		sum[i] = 0;
	}

	int sum_i = 0;

	/*
		variable d is used to record the temporary value of other variable
	*/
	int d = 0;

	LinkNode<int> * ptr1 = l2[sum_i]->getHead()->link;
	while (ptr1->link != NULL) {
		if (ptr1->data == 0) {

			sum[sum_i] = 0;
			sum[++sum_i] = 0;
			sum[++sum_i] = 0;
		} else {
			if (ptr1->data < 100) {

				sum[sum_i] = (ptr1->data) % 10;

				sum[++sum_i] = (ptr1->data) / 10;

				sum_i += 1;
			}
			if (ptr1->data >= 100) {

				sum[sum_i] = (ptr1->data) % 10;
				sum[++sum_i] = ((ptr1->data) / 10) % 10;
				sum[++sum_i] = (ptr1->data) / 100;
			}
		}

		sum_i += 1;

		ptr1 = ptr1->link;
	}

	for (int i = 1; i < m_len; i ++) {
		ptr1 = l2[i]->getHead()->link;

		/*
			Declare the variable c to resore the num carried
		*/
		int c = 0;

		sum_i = i;	// Be careful about the problem of carrying, called "½øÎ»" in Chinese
		while (ptr1->link != NULL) {
			
			if (ptr1->data == 0) {

				sum[sum_i] += 0;
				sum[++sum_i] += 0;
				sum[++sum_i] += 0;
			} else {
				if (ptr1->data < 100) {

					sum[sum_i] += c;
					sum[sum_i] += (ptr1->data) % 10;
					c = sum[sum_i] / 10;
					sum[sum_i] -= c * 10;

					sum[++sum_i] += c;
					sum[sum_i] += (ptr1->data) / 10;
					c = sum[sum_i] / 10;
					sum[sum_i] -= c * 10;

					sum[++sum_i] += c;
					c = sum[sum_i] / 10;
					sum[sum_i] -= c * 10;
				}
				if (ptr1->data >= 100) {

					sum[sum_i] += c;
					sum[sum_i] += (ptr1->data) % 10;
					c = sum[sum_i] / 10;
					sum[sum_i] -= c * 10;

					sum[++sum_i] += c;
					sum[sum_i] += ((ptr1->data) / 10) % 10;
					c = sum[sum_i] / 10;
					sum[sum_i] -= c * 10;

					sum[++sum_i] += c;
					sum[sum_i] += (ptr1->data) / 100;
					c = sum[sum_i] / 10;
					sum[sum_i] -= c * 10;
				}
			}

			sum_i += 1;

			ptr1 = ptr1->link;
		}
	}

	LinkedList * l3 = new LinkedList;

	/*
		In order to delete the 0 in the front part of the array
	*/
	for (int i = sum_len - 1; i >= 0; i --) {
		if (sum[i] != 0) {
			sum_len = i + 1;

			break;
		}
	}

	sum_i = 0;
	int work_n = 0;
	while (sum_i < sum_len) {
		if (sum[sum_i + 2] != 0) {

			work_n = sum[sum_i];	
			sum_i += 1;
			
			work_n += sum[sum_i] * 10;
			sum_i += 1;

			work_n += sum[sum_i] * 100;

			l3->insert(work_n);
		} else {
			if (sum[sum_i + 1] != 0) {
				work_n = sum[sum_i];
				
				sum_i += 1;
				work_n += sum[sum_i] * 10;

				sum_i += 1;

				l3->insert(work_n);
			} else {
				
				l3->insert(sum[sum_i]);

				sum_i += 2;
			}

		}

		sum_i += 1;

		work_n = 0;
		if (sum_i + 2 >= sum_len) {

			if (sum[sum_i] > 0 && sum_i < sum_len) {
				work_n = sum[sum_i];
			} 
			
			if (sum[sum_i + 1] > 0 && sum_i + 1 < sum_len) {
				work_n += sum[sum_i + 1] * 10;
			}

			if (work_n > 0) {
				l3->insert(work_n);	
			}

			break;
		}
	}

	/*
		I Don't know why the following order executed 
		 will cause this program break down
	*/
	// delete[] sum;

	return l3;
}

void Algorithm::reSizeLinkedLists(LinkedList **l2, int m_len, int m_len_before) {
	/*
		Retrive the memory of **l2,
	*/
	for (int i = 0; i < m_len_before; i ++) {
		l2[i]->makeEmpty();
	}

	delete[] l2;

	l2 = new LinkedList * [m_len];
}

void Algorithm::factorial(int x) {

	/*
		Declare the working variable to
		 restore the num to multiplied with
	*/
	int m = x - 1;

	/*
		Now start the process of factorial
	*/

	/*
		Declare the working variable of l1 to
			restore the middle result
	*/
	string x_str = to_string((long long)x);
	LinkedList * l1  = this->constructList(x_str);

	while (m >0) {
		
		x_str = this->list2String(l1);
		
		l1 = this->Multiply(x_str, m);

		m -= 1;
	}

	cout<< "--------------!"<< endl;
	l1->printNumber();
	cout<< "--------------!"<< endl;
}

string Algorithm::list2String(LinkedList * l1) {
	string str1 = "";

	LinkNode<int> * p = l1->getHead()->link;

	int nums_len = l1->getLength() * 3;
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

	for (int i = num_i - 1; i >= 0; i --) {
		if (mark_show) {
			if (nums[i] != 0) {
				str1 += std::to_string(long long (nums[i]));
				mark_show = false;
			}
		} else {
			str1 += std::to_string(long long (nums[i]));
		}
	}

	delete[] nums;

	return str1;
}