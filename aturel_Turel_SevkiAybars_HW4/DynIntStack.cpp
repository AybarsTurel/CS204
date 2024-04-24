#include <iostream>
#include "dynintstack.h"
using namespace std;

/*
This class was taken from CS204 Lecture materials. It stores the function name and process in a node.
*/

//************************************************
// Constructor to generate an empty stack.       *
//************************************************
DynIntStack::DynIntStack()
{
	top = NULL; 
}

//************************************************
// Member function push pushes the argument onto *
// the stack.                                    *
//************************************************
void DynIntStack::push(string func, string word)
{
	StackNode *newNode;

	// Allocate a new node & store Num
	newNode = new StackNode;
	newNode->definingWord = word;
	newNode->function = func;

	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = top;
		top = newNode;
	}
}

//****************************************************
// Member function pop pops the value at the top     *
// of the stack off, and copies it into the variable *
// passed as an argument.                            *
//****************************************************
void DynIntStack::pop(string &func, string & word)
{
	StackNode *temp;

	if (isEmpty())
	{
		cout << "The stack is empty.\n";
	}
	else	// pop value off top of stack
	{
		func = top->function;
		word = top->definingWord;
		temp = top->next;
		delete top;
		top = temp;
	}
}

//****************************************************
// Member funciton isEmpty returns true if the stack *
// is empty, or false otherwise.                     *
//****************************************************
bool DynIntStack::isEmpty(void)
{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}

void DynIntStack::clear()
{
	string function;
	string definingWord;// Dummy variable for dequeue

	while(!isEmpty())
		pop(function, definingWord); //delete all elements
}

