# ifndef __CCS_H__
# define __CCS_H__

# include<iostream>
# include<cmath>
# include<string>
# include"LinkedStack.h"
# include"TemplateLinkedStack.h"
# include"Queue.h"

using namespace std;

class Calculator_StringInput {
public:
	int isp(string ch);
	int icp(string ch);

	bool isdigit(string ch);

	void Clear();	// clear the stack

	void pushOrPopProcess(LinkedStack &s1, string &ch, string &ch1, int &i, bool &Loop_mark);
	
	double run(string expression);	// Expression is restored by a string variable

	void DoOperand(string op);
	bool get2Operand(double &left, double &right);	// derive two operands from the stack
	void AddOperand(double value);

	double getSummary();
private: 
	TemplateLinkedStack<double> s;	// Declare the private data member stack, no parameter

	Queue q2;	// restore the ouput;

	double summary;
};

double Calculator_StringInput::getSummary() {
	double sum = this->summary;
	return sum;
}

void Calculator_StringInput::pushOrPopProcess(LinkedStack &s1, string &ch, string &ch1, int &i, bool &Loop_mark) {
	if (this->isdigit(ch)) {
		// operand, pushed to q2
		q2.Push(ch);

		Loop_mark = true;
	} else {
		s1.getTop(ch1);	// ch1 currenly restore the top element of s1

		if (isp(ch1) < icp(ch)) {
				// newly input ch is higher level than ch1, so pushed to s1
				s1.Push(ch);

				Loop_mark = true;

			} else if (isp(ch1) > icp(ch)) {
				// newly input ch is lower level than ch1, so popped from s1
				// and ch1 pushed to s2
				s1.Pop(ch1, i);
				q2.Push(ch1);

				Loop_mark = false;
				
			} else {	// ch1 has the equal level to ch(because they re "(" and ")")
				s1.Pop(ch1, i);

				Loop_mark = true;
			}
	}
}

bool Calculator_StringInput::get2Operand(double &left, double &right) {
	// Derive two operands from the stack s
	if (s.IsEmpty() == true) {
		cout<< "Error : Lack of left operand ! "<< endl;
		return false;
	}

	// Declare the job variable, restore the index popped from stack s
	int i = NULL;
	s.Pop(right, i);

	if (s.IsEmpty() == true) {
		cout<< "Error : Lack of right operand ! "<< endl;
		return false;
	}

	s.Pop(left, i);

	return true;
}

void Calculator_StringInput::DoOperand(string op) {
	// proceed the compute process
	double left;
	double right;
	double value;

	bool result;
	result = this->get2Operand(left, right);

	if (result) {
		
		if (op == "+") {
			value = left + right;
			s.Push(value);
			cout<< "The value is : "<< value<< endl;
			
			this->summary = value;
		} else if (op == "-") {
			value = left - right;
			s.Push(value);
			cout<< "The value is : "<< value<< endl;

			this->summary = value;
		} else if (op == "*") {
			value = left * right;
			s.Push(value);
			cout<< "The value is : "<< value<< endl;
			
			this->summary = value;
		} else if (op == "/") {

			if (right == 0.0) {
				cout<< "Divided by 0 ! "<< endl;
				this->Clear();	// »Ù≥˝0£¨‘Ú±®¥Ì£¨«Â’ª
			} else {	
				value = left / right;
				s.Push(value);
				cout<< "The value is : "<< value<< endl;
				
				this->summary = value;	
			}
		}

	} else {
		this->Clear();
	}
}

void Calculator_StringInput::AddOperand(double value) {
	this->s.Push(value);
}

double Calculator_StringInput::run(string expression) {
	LinkedStack s1;	// restore the operands

	string ch = "#";
	s1.Push(ch);
	ch = "";

	string ch1;
	string op;
	int i;	// declare the job variable i to 
			// restore the value from the operation pop

	/* Description
		
		The job variable signal_mark record the value state of ch
		For example, signal_mark = -1 refers to the state of ch recording a number
		 and on the contrary, equaling 1 stands for the state restoring a "("
	*/
	int signal_mark = 1;

	bool Loop_mark = false;

	for (int exprs_i = 0; exprs_i < expression.length(); exprs_i ++) {
		
		if (expression[exprs_i] == '-' && signal_mark == 1) {
			ch.push_back(expression[exprs_i]);

			signal_mark = -1;
			continue;
		}

		if (expression[exprs_i] == '*' || expression[exprs_i] == '/' || expression[exprs_i] == '%' || expression[exprs_i] == '+' || expression[exprs_i] == '-' || expression[exprs_i] == '(' || expression[exprs_i] == ')' || expression[exprs_i] == '#') {
			
			if (expression[exprs_i] == '(') {
				signal_mark = 1;
			} else {
				signal_mark = -1;
			}

			if (ch != "") {
				q2.Push(ch);	// Push the complete number restored by ch as the past value
			}
			ch = "";

			
			ch.push_back(expression[exprs_i]);
			
			while (! Loop_mark) {
				this->pushOrPopProcess(s1, ch, ch1, i, Loop_mark);
			}

			ch = "";

		} else {	// Attention: the only signals probably appearing is * / % ( ) + - #, then the 10 numbers and the signal "." will lead to the following order executed

			ch.push_back(expression[exprs_i]);
			signal_mark = -1;
		}

		Loop_mark = false;
	}

	if (ch.length() > 0) {
		if (!(ch == "+" || ch == "-" || ch == "*" || ch == "/" || ch == "(" || ch == ")")) {
			q2.Push(ch);
		}
	}

	ch = "#";

	while (! Loop_mark) {
		this->pushOrPopProcess(s1, ch, ch1, i, Loop_mark);
	}

	q2.print();

	double newOperand;

	// Declare a job variable to restore the current position
	LinkedNode * ptr = q2.getFront();

	while (ptr != NULL) {
		ch = ptr->data;

		if (ch == "+" || ch == "-" || ch == "*" || ch == "/") {
			this->DoOperand(ch);
		} else {
			newOperand = (double)(atof(ch.c_str()));
			this->AddOperand(newOperand);
		}

		ptr = ptr->next;
	}

	cout<< "The summary is : "<< this->getSummary()<< endl;;
	
	return this->getSummary();
}

int Calculator_StringInput::isp(string ch) {
	if (ch == "*" || ch == "/" || ch == "%") {
		return 5;
	} else if (ch == "+" || ch == "-") {
		return 3;
	} else if (ch == "(") {
		return 1;
	} else if (ch == ")") {
		return 6;
	} else if (ch == "#") {
		return 0;
	}
	
}

int Calculator_StringInput::icp(string ch) {
	if (ch == "*" || ch == "/" || ch == "%") {
		return 4;
	} else if (ch == "+" || ch == "-") {
		return 2;
	} else if (ch == "(") {
		return 6;
	} else if (ch == ")") {
		return 1;
	} else if (ch == "#") {
		return 0;
	}
}

bool Calculator_StringInput::isdigit(string ch) {
	if (ch == "*" || ch == "/" || ch == "%" || ch == "(" || ch == ")" || ch == "+" || ch == "-" || ch == "#") {
		return false;
	} else {
		return true;
	}
}

void Calculator_StringInput::Clear() {
	this->s.makeEmpty();	
}

# endif