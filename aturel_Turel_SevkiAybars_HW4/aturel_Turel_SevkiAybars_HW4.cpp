/*************
Purpose: This code was writen to store the service demands for students and instructors in queue to serve first to fulfill the request of the person who requests it first. To execute the function we have used stacks.
Usage: There are three .txt files that name are input1.txt, input2.txt and input3.txt. However, these file are not essential for running code but user has to add at least one txt file that includes function. In this file, program gets function name as a first line, after that it takes processes. 
Author: Sevki Aybars Turel 28238
Date: 20/11/2021
Any known bugs: There are any known bugs. However, to running code, user have to enter at least one input.txt file that includes function and processes.
References: IntQueue.cpp, IntQueue.h, DynIntStack.h, DynIntStack.cpp, DynIntQueue.cpp and DynIntQueue.h files were taken from CS204 Week 5 lecture materials. This files were updated according to new needs to run code. Main menu, processARequest() and processARequest(string funcName) were taken from homework file.

**************/

#include<iostream>
#include<string>
#include<fstream>
#include"IntQueue.h"
#include"DynIntQueue.h"
#include"DynIntStack.h"

using namespace std;

struct processInFunc // It is a struct that stores wanted process
{
	string process;
	processInFunc *next;
	processInFunc::processInFunc()
	{}

	processInFunc::processInFunc(const string& a, processInFunc*b)
		: process(a), next(b)
	{}

};

struct functionName // It is a struct that stores function name
{
	string name;
	functionName *right;
	processInFunc *next;

	functionName::functionName()
	{}

	functionName::functionName(const string & a, functionName * b, processInFunc * c)
		: name(a), right(b), next(c)	
	{}

};

struct instructorInfos // It is a struct that contains the demanded service of instructor and his/her name, id
{
	int instructorID;
	string instructorName;
	string function;

	instructorInfos::instructorInfos()
	{}

	instructorInfos::instructorInfos(int a, string b, string c)
		:instructorID(a), instructorName(b), function(c)
	{}
};

functionName *servicesHead = NULL; // Global variable pointer that point the first node of linked list.
IntQueue instructorQueue(100); // Global variable that creates queue that stores the instructorInfos.
DynIntQueue studentQueue; // Global variable that stores the demanded service of students, their id's and names.
DynIntStack sharedStack; // Global variable that used in printing process in order.

void PrintFuncForLinkedList() // Print function for service head that stores the linked list of functions and processes. 
{
	functionName *temp = servicesHead;

	while(temp != NULL)
	{
		cout << temp->name << ":" << endl;
		processInFunc *temp2 = temp->next;
		temp = temp->right;
		while(temp2 != NULL)
		{
			cout << temp2->process;
			if(temp2->next == NULL)
			{
				cout << ".";
			}
			else
			{
				cout << ",";
			}
			temp2 = temp2->next;
		}
		cout << endl;

	}
}

void AddInstructorRequest() // It takes request from instructor and put them into the instructor queue.
{
	bool serviceExists = false; 
	string service, instructorName;
	int ID;
	functionName *temp = servicesHead;
	instructorInfos infos;
	cout << "Add a service <function> that the instructor wants to use:" << endl;
	cin >> service;
	while(temp != NULL && serviceExists == false)
	{
		if(temp->name == service)
		{
			serviceExists = true; // requested service is in the linked list or not
		}
		else
		{
			temp = temp->right;
		}
	}
	if(serviceExists) // requested service in the linked list
	{
		cout << "Give instructor's name: ";
		cin >> instructorName;
		cout << "Give instructor's ID <an int>: ";
		cin >> ID;
		instructorQueue.enqueue(instructorInfos(ID,instructorName,service)); // it creates structs that  includes instructor'S id, name and demand. After that it add this struct into the queue.
		cout << "Prof. " << instructorName << "'s service request of " << service << " has been put in the instructor's queue." << endl;
		cout << "Waiting to be served..." << endl;
		/*while(!instructorQueue.isEmpty())
		{
			instructorQueue.dequeue(infos);
			cout << infos.instructorID << infos.instructorName << infos.function << endl;
		}
		instructorQueue.enqueue(instructorInfos(ID,instructorName,service));*/
		
	}
	else
	{
		cout <<  "The requested service <function> does not exist." << endl;
		cout << "GOING BACK TO MAIN MENU" << endl;
	}
}

void AddStudentRequest() // It takes request from student and put them into the student queue.
{
	bool serviceExists = false;
	string service, studentName;
	int ID;
	functionName *temp = servicesHead;
	cout << "Add a service <function> that the student wants to use:" << endl;
	cin >> service;
	while(temp != NULL && serviceExists == false)
	{
		if(temp->name == service)
		{
			serviceExists = true; // requested service is in the linked list or not
		}
		else
		{
			temp = temp->right;
		}
	}
	if(serviceExists) // requested service in the linked list
	{
		cout << "Give student's name: ";
		cin >> studentName;
		cout << "Give student's ID <an int>: ";
		cin >> ID;
		studentQueue.enqueue(ID, service, studentName); // it takes student's id, name and demanded service. After that it add these information into the student queue.
		cout <<  studentName << "'s service request of " << service << " has been put in the student's queue." << endl;
		cout << "Waiting to be served..." << endl;
		/*while(!studentQueue.isEmpty())
		{
			studentQueue.dequeue(ID, service, studentName);
			cout << ID << service << studentName << endl;
		}
		studentQueue.enqueue(ID,service,studentName);*/
	}
	else
	{
		cout <<  "The requested service <function> does not exist." << endl;
		cout << "GOING BACK TO MAIN MENU" << endl;
	}

}

void processARequest(string functionNameStr) // taken from homework file.
{
	string functionNameTemp2,operationTemp2;
	functionName * temp = servicesHead;
	DynIntStack tempStack1;
	DynIntStack tempStack2;
	while(temp->name != functionNameStr)
	{
		temp = temp->right;
	}
	processInFunc *temp2 = temp->next;
	while (temp2 != NULL) 
	{    
		string operation = temp2->process;
		if(operation.substr(0,6) =="define") // it checks what is the process
		{
			sharedStack.push(functionNameStr,operation); 
		} 
		else if (operation.substr(0,4) =="call") // it checks what is the process
		{ 
			string funcNameinFunc = operation.substr(5); 
			cout << "Calling " << funcNameinFunc << " from " << functionNameStr << endl;
			processARequest(funcNameinFunc);			

		} 
		else //print the stack … 
		{
			string functionNameTemp, operationTemp;
			cout << "PRINTING THE STACK TRACE:" << endl;
			if(sharedStack.isEmpty())
			{
				cout << "The stack is empty" << endl;
			}
			while (!sharedStack.isEmpty())
			{
				sharedStack.pop(functionNameTemp,operationTemp);
				//cout << functionNameTemp << " " << operationTemp << endl;
				tempStack1.push(functionNameTemp,operationTemp);
			}
			while(!tempStack1.isEmpty())
			{
				tempStack1.pop(functionNameTemp,operationTemp);
				cout << functionNameTemp << " " << operationTemp << endl;
				sharedStack.push(functionNameTemp,operationTemp);
			}
			
		}
		temp2 = temp2->next;
	}
	cout<<functionNameStr<<" is finished. Clearing the stack from it's data... " <<endl; 
	while(!sharedStack.isEmpty()) // in the two while loop, program searchs the last function members ant it pop these function members in shared stack.
	{
		sharedStack.pop(functionNameTemp2,operationTemp2);
		if(functionNameTemp2 != functionNameStr)
		{
			tempStack2.push(functionNameTemp2,operationTemp2);
		}
	}
	while(!tempStack2.isEmpty())
	{
		tempStack2.pop(functionNameTemp2,operationTemp2);
		sharedStack.push(functionNameTemp2,operationTemp2);
	}
	system("pause");
	if (sharedStack.isEmpty())
	{
		cout << "The stack is empty." << endl;
	}
} 

void processARequest() // function was taken from homework file.
{
	if (!instructorQueue.isEmpty()) 
	{  
		instructorInfos infos;
		instructorQueue.dequeue(infos); // program takes the structs that includes instructor information.
		string functionName = infos.function; // program take the name of the function to proceed it.
		cout << "Processing instructors queue..." << endl;
		cout << "Processing prof. " <<  infos.instructorName << "'s request <with ID " << infos.instructorID << "> of service <function>:" <<endl;
		cout << functionName << endl;
		processARequest(functionName); 
		cout<<"GOING BACK TO MAIN MENU"<<endl; 
	}
	else if (!studentQueue.isEmpty())
	{ 
		int ID;
		string functionName;
		string name;
		cout << "Instructors queue is empty. Proceeding with students queue..." << endl;
		studentQueue.dequeue(ID,functionName, name); // program takes the information about student
		cout << "Processing " << name << "'s request <with ID " << ID << "> of service <function>: " << endl;
		cout << functionName << endl;
		cout << "-------------------------------------------------------------------------------" << endl;
		processARequest(functionName); // program will proceed the demanded function.
		cout<<"GOING BACK TO MAIN MENU"<<endl;
	}
	else 
	{ 
		cout<<"Both instructor's and student's queue is empty.\nNo request is processed."<<endl<<"GOING BACK TO MAIN MENU"<<endl; 
	} 
}

void DeletingLinkedList()
{
	while(servicesHead != NULL)
	{
		functionName *temp = servicesHead;
		processInFunc *temp2 = servicesHead->next;
		while(temp2 != NULL)
		{
			processInFunc *temp3 = new processInFunc;
			temp3 = temp2->next;
			delete temp2;
			temp2 = temp3;
		}
		servicesHead = temp->right;
		delete temp;
	}
}


int main()
{
	string fileName, function, processInFunc1, choice, info;
	bool correctionOfFile = true; // it was used to terminate whole program when one of the files cannot be opened.
	ifstream infoFile;
	cout << "If you want to open a service <function> defining file, then press <Y/y> for 'yes', otherwise press any single key" << endl;
	cin >> choice;
	while(choice == "Y" || choice == "y")
	{
		cout << "Enter the input file name: ";
		cin >> fileName;
		infoFile.open(fileName.c_str());
		if(infoFile.fail())
		{
			cout << fileName << " cannot be opened! Program terminated!" << endl;
			correctionOfFile = false;
			break;
		}
		functionName *temp = servicesHead;
		getline(infoFile,function);
		int index = function.find(":");
		function = function.substr(0,index);
		getline(infoFile,info);
		index = info.find(";");
		info = info.substr(0,index);
		if(temp == NULL)
		{
			processInFunc *newProcess = new processInFunc(info,NULL);
			functionName *newFunc = new functionName(function,NULL,newProcess);
			servicesHead = newFunc;
			temp = newFunc;
		}
		else
		{
			while(temp->right != NULL)
			{
				temp = temp->right;
			}
			processInFunc *newProcess = new processInFunc(info,NULL);
			functionName *newFunc = new functionName(function,NULL,newProcess);
			temp->right = newFunc;
			temp = temp->right;
		}

		while(getline(infoFile,info))
		{
			index = info.find(";");
			info = info.substr(0,index);
			processInFunc *tempProcess = temp->next;
			while(tempProcess->next != NULL)
			{
				tempProcess = tempProcess->next;
			}
			processInFunc *newProcess2 = new processInFunc(info,NULL);
			tempProcess->next = newProcess2;
		}
		cout << "Do you want to open another service defining file?" << endl;
		cout <<	"Press <Y/y> for 'yes', otherwise press anykey" << endl;
		cin >> choice;
		infoFile.close();
	}
	if(correctionOfFile)
		{
			cout << "--------------------------------------------------------------------" << endl;
			cout << "PRINTING AVAILABLE SERVICES <FUNCTIONS> TO BE CHOSEN FROM THE USERS " << endl;
			cout << "--------------------------------------------------------------------" << endl;
			PrintFuncForLinkedList();
			while (true)
			{ 
				cout << endl; 
				cout<<"**********************************************************************"<<endl 
					<<"**************** 0 - EXIT PROGRAM                        *************"<<endl 
					<<"**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST   *************"<<endl
					<<"**************** 2 - ADD A STUDENT SERVICE REQUEST       *************"<<endl 
					<<"**************** 3 - SERVE (PROCESS) A REQUEST           *************"<<endl 
					<<"**********************************************************************"<<endl; 
					cout << endl; 
					int option; 
					cout << "Pick an option from above (int number from 0 to 3): "; 
					cin>>option;
					switch (option) 
					{ 
						case 0: cout<<"PROGRAM EXITING ... "<<endl;
							DeletingLinkedList();
							system("pause"); 
							exit(0); 
						case 1: 
							AddInstructorRequest(); 
							break; 
						case 2: 
							AddStudentRequest(); 
							break; 
						case 3: 
							processARequest(); 
							break; 
						default: 
							cout<<"INVALID OPTION!!! Try again"<<endl; 
					}//switch }//while (true)
		}
	}
	DeletingLinkedList();
	PrintFuncForLinkedList();
	return 0;
}
