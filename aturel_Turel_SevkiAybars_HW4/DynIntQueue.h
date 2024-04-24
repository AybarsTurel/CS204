#ifndef DYNINTQUEUE_H
#define DYNINTQUEUE_H

/*
This class was taken from CS204 Lecture materials. Stuct whose name is QueueNode upadeted according to new needs. It contains information related to students.
*/


using namespace std;
struct QueueNode
{
	int studentID;
	string function;
	string studentName;
	QueueNode *next;
	QueueNode(int num, string functionName, string name, QueueNode *ptr = NULL)
	{
		studentID = num;
		function = functionName;
		studentName = name;
		next = ptr;
	}
};

class DynIntQueue
{
private:
	// These track the front and rear of the queue.
	QueueNode *front;
	QueueNode *rear;	
public:
	// Constructor.
	DynIntQueue();
	
	// Member functions.
	void enqueue(int,string,string);
	void dequeue(int &, string &, string &);
	bool isEmpty() const;     
	void clear();
};
#endif