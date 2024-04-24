#include <iostream>
#include "DynIntQueue.h"

/*
This class was taken from CS204 Lecture materials. Struct whose name is QueueNode upadeted according to new needs. It contains information related to students.
*/


using namespace std;

//************************************************
// Constructor. Generates an empty queue         *
//************************************************
DynIntQueue::DynIntQueue()
{
	front = NULL;
	rear = NULL;   
}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//********************************************
void DynIntQueue::enqueue(int num, string functionName, string name)
{       
	if (isEmpty())   //if the queue is empty
	{	//make it the first element
		front = new QueueNode(num, functionName, name);
		rear = front;
	}
	else  //if the queue is not empty
	{	//add it after rear
		rear->next = new QueueNode(num, functionName, name);
		rear = rear->next;
	} 
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into num. *
//**********************************************
void DynIntQueue::dequeue(int &num, string &functionName, string &name)
{
	QueueNode *temp;
	if (isEmpty())
	{
		cout << "Attempting to dequeue on empty queue, exiting program...\n";
		exit(1);
	}
	else //if the queue is not empty
	{	//return front's value, advance front and delete old front
		num = front->studentID;
		functionName = front->function;
		name = front->studentName;
		temp = front;
		front = front->next;
		delete temp;      
	}
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool DynIntQueue::isEmpty() const
{
	if (front == NULL)
		return true;
	else 
		return false;
}

//********************************************
// Function clear dequeues all the elements  *
// in the queue.                             *
//********************************************
void DynIntQueue::clear()
{
	int studentID;
	string function;
	string studentName;// Dummy variable for dequeue

	while(!isEmpty())
		dequeue(studentID, function, studentName); //delete all elements
	#ifdef _DEBUG
		cout << "queue cleared\n";
	#endif
}