#include <iostream>
#include "IntQueue.h"
using namespace std;

/*
This class was taken from CS204 Lecture materials. It contains information related to instructor and store them into queue.
*/

//*****************************************
// Constructor - creates an empty queue   *
// with given number of elements          *
//*****************************************
struct instructorInfos
{
	int instructorID;
	string instructorName;
	string function;
};

IntQueue::IntQueue(int s)
{
	queueArray = new instructorInfos[s];
	queueSize = s;
	front = -1;
	rear = -1;
	numItems = 0;
}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//********************************************
void IntQueue::enqueue(instructorInfos num)
{
	if (isFull())
    { 
         cout << "The queue is full.";
    }
	else
	{
		// Calculate the new rear position circularly.
		rear = (rear + 1) % queueSize;
		// Insert new item.
		queueArray[rear] = num;
		// Update item count.
		numItems++;
	}
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into num. *
//**********************************************
void IntQueue::dequeue(instructorInfos &num)
{
	if (isEmpty())
	{
       cout << "Attempting to dequeue on empty queue, exiting program...\n";
       exit(1);
    }
	else
	{
		// Move front.
		front = (front + 1) % queueSize;
		// Retrieve the front item.
		num = queueArray[front];
		// Update item count.
		numItems--;
	}
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool IntQueue::isEmpty() const
{
	if (numItems > 0)
		return false;
	else
		return true;	
}

//********************************************
// Function isFull returns true if the queue *
// is full, and false otherwise.             *
//********************************************
bool IntQueue::isFull() const
{
	if (numItems < queueSize)
		return false;
	else
		return true;
}

//*******************************************
// Function clear resets the front and rear *
// indices, and sets numItems to 0.         *
//*******************************************
void IntQueue::clear()
{
	front =  - 1;
	rear =  - 1;
	numItems = 0;
}