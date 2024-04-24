#ifndef INTQUEUE_H
#define INTQUEUE_H

/*
This class was taken from CS204 Lecture materials. Struct whose name is instructorInfos was added according to new needs. It contains information related to instructor.
*/

class IntQueue
{
private:
	struct instructorInfos *queueArray;
	int queueSize;  //capacity of queue
	int front;
	int rear;
	int numItems;  //# of elements currently in the queue
public:
	IntQueue(int);  //constructor, parameter is capacity
	void enqueue(instructorInfos); 
  	void dequeue(instructorInfos &);
  	bool isEmpty() const; 
  	bool isFull() const;
  	void clear();  //removes all elements
};
#endif