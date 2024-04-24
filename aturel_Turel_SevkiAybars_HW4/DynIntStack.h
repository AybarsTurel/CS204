#include <iostream>
using namespace std;

/*
This class was taken from CS204 Lecture materials. Struct that contains name of function and process was added. It has the same logic with intStack but instead of storing int, it stores struct.
*/

struct StackNode
{
	string function;
	string definingWord;
	StackNode *next;
};

class DynIntStack
{
private:
	StackNode *top;

public:
	DynIntStack(void);
	void push(string,string);
	void pop(string & ,string &);
	bool isEmpty(void);
	void clear(void);
};
