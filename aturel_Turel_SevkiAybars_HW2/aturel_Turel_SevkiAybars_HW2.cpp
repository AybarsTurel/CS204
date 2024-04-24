/*************
Purpose: This program is to store data in the add-drop period and display them at the end of the add-drop period.
Usage: There is a .txt file that name is coursesAndStudent. In this file, program gets initial data about courses and students. In this program strutils.cpp and strutils.h files. 
Author: Sevki Aybars Turel 28238
Date: 25/10/2021
Any known bugs: There are any known bugs.
References: strutils.h and strutils.cpp files has been taken from CS201 Recitation Materials. Additionally, DeleteList, AddNewLesson and DisplayList function were taken from CS 204 Lecture Notes. 
**************/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "strutils.h"

using namespace std;

struct courseNode // It is a simple struct that were given in the homework file. It stores Course Name, Course Code, vector of student ID's and next pointer to make it linkedlist.
{
	string courseCode, courseName;
	vector<int> studentsAttendingIDs;
	courseNode * next;
	courseNode::courseNode()
	{}

	courseNode::courseNode (const string & a, const string & b, const vector<int> & c ,courseNode * link)
		: courseCode(a), courseName(b), studentsAttendingIDs(c), next(link)
	{}

};

void SortingFuncForVector(vector<int> & studentIDs) // This function were taken from CS201 Lecture Notes
{ // This function starts from the beginning of the vector and it compare other number to find the smallest one.
	int temp, minIndex;
	int elementsInVector = studentIDs.size();
	for(int i = 0; i < elementsInVector - 1; i++)
	{
		minIndex = i;

		for(int k = i + 1; k < elementsInVector; k++)
		{
			if(studentIDs[k] < studentIDs[minIndex])
			{
				minIndex = k;
			}
		}
		temp = studentIDs[i];
		studentIDs[i] = studentIDs[minIndex];
		studentIDs[minIndex] = temp;
	}
}

bool lessonCheckerInList(courseNode *head, const string & courseCode)
{ // This function checks any certain coursecode is in the linked list or not.
	// If there is a node that includes coursecode it will be used to update vector of student id.
	courseNode *ptr = head;
	while(ptr != NULL)
	{
		if(ptr->courseCode == courseCode)
		{
			return false;
		}
		ptr = ptr->next;
	}
	return true;


}

bool SameIdCheckerInCourse(vector<int> & studentIDs, int studentId)
{ // This function will check the certain id is in the vector of students id or not so the same id will not be added the vector.
	for(int i = 0; i < studentIDs.size(); i++)
	{
		if(studentIDs[i] == studentId)
		{
			return false;
		}
	}
	return true;
}

courseNode * AddNewLesson(courseNode * head, string courseName, string courseCode, int studentID) // This function have been taken from CS204 Lecture materials and updated accoding to new needs.
{ 
    courseNode *  ptr = head; 

	if (head == NULL || courseName < head->courseName)        
    {   
		courseNode * temp = new courseNode;  //node to be inserted 
		temp->courseCode = courseCode;
		temp->courseName = courseName;
		temp->studentsAttendingIDs.push_back(studentID); // This part will add student ID to vector of studentsAttendingID.
		SortingFuncForVector(temp-> studentsAttendingIDs);
		temp->next = head; //connect the rest
		return temp;
    }
	while (ptr->next != NULL && ptr->next->courseName < courseName)
    {   
		ptr = ptr->next;
    } 
    //now insert node with newkey after where ptr points to
	courseNode * temp = new courseNode;  //node to be inserted 
	temp->courseName = courseName;
	temp->courseCode = courseCode;
	temp->studentsAttendingIDs.push_back(studentID);
	SortingFuncForVector(temp-> studentsAttendingIDs);
	temp->next = ptr->next; //connect the rest
	ptr->next = temp;

    return head;
}

void PrintVector(const vector<int> & vectorOfStudents) // It is a function taht will display the members of the vector.
{
	for(int i = 0; i < vectorOfStudents.size(); i++)
	{
		cout << vectorOfStudents[i] << " ";
	}
}

void DisplayList(courseNode * head) // It will display the nodes with all members.
{
	courseNode * ptr = head;
    while (ptr != NULL) 
	{
		cout << ptr ->courseCode << " " << ptr->courseName << ":";
		PrintVector(ptr->studentsAttendingIDs);
		cout << endl;
		ptr = ptr->next;
	}
	cout << endl<<endl;
}

void TakingChoice(int & choice) // It is a simple input function that takes choice from user.
{
	cout << "Please select one of the choices: " << endl;
	cout << "1. Add to List" << endl;
	cout << "2. Drop from List" << endl;
	cout << "3. Display List" << endl;
	cout << "4. Finish Add/Drop and Exit" << endl;
	cin >> choice;
}

bool NumberChecker(string s) // This checks the certain strings include number or not.
{
	if(s == "1" || s == "2" || s == "3" || s == "4" || s == "5" || s == "6" || s == "7" || s == "8" || s == "9" || s == "0")
	{
		return true;
	}
	return false;
}

void DeleteList(courseNode* head) // This function were taken from CS204 Lecture notes. It simply deletes the nodes in the linked list.
{
	courseNode* temp;
	while (head != NULL)
	{
		temp = head->next;
		delete head;
		head = temp;
	}
}


void SwapWithLastElementOfVector(vector<int> & studentsAttendingIDs, int studentID) // It finds the certain id to be deleted and change its position.   
{//It puts the certain id to last element of vector to destroy it with a pop_back() function of vectors.
	int sizeOfVector = (studentsAttendingIDs.size() - 1);
	for(int i = 0; i < sizeOfVector; i++)
	{
		if(studentsAttendingIDs[i] == studentID)
		{
			int tempID = studentsAttendingIDs[i];
			studentsAttendingIDs[i] =  studentsAttendingIDs[sizeOfVector];
			studentsAttendingIDs[sizeOfVector] = tempID;
		}
	}
}

void FinalDisplayList(courseNode * head) // It is updated version of DisplayList function to show some extra info.
{
	courseNode * ptr = head;
    while (ptr != NULL) 
	{
		
		if((ptr->studentsAttendingIDs.size()) < 3)
		{
			cout << ptr ->courseCode << " " << ptr->courseName << " ";
			PrintVector(ptr->studentsAttendingIDs);
			cout << " -> This course will be closed this semester." << endl;
		}
		else
		{
			cout << ptr ->courseCode << " " << ptr->courseName << ":";
			PrintVector(ptr->studentsAttendingIDs);
			cout << endl;
		}
		ptr = ptr->next;
	}
	cout << endl<<endl;
}

int main()
{
	string filename, line, courseCode, courseName;
	int intStudentID, userChoice = 0;
	ifstream inputFile;
	string a,s;
	string word;
	
	cout << "Please enter filename: ";

	cin >> filename;

	inputFile.open(filename.c_str()); // opening file

	if(inputFile.fail()) // checks the file is opened successfully or not.
	{
		cout << "File cannot be opened!";
	}
	else
	{
		cout << "Succesfully opened file " << filename << endl;

		courseNode * head = NULL; // it is a pointer that shows the head of linked list.

		while(getline(inputFile, line)) // it reads file line by line
		{
			istringstream input(line);
			
			input >> courseCode >> courseName >> intStudentID; // all lines continues coursecode, coursename and student id.

			if((lessonCheckerInList(head, courseCode))) // checks certain course has any node or not
			{
				head = AddNewLesson(head, courseName, courseCode, intStudentID); // if not it creates new node and add to head.
			}
			else
			{
				courseNode *temp = head; // it is new pointer that points head of the linked list.
				while(temp->courseName != courseName) // until they find the node that includes certain course ptr will be shifted.
				{
					temp = temp->next;
				}
				temp->studentsAttendingIDs.push_back(intStudentID); // it puts the id to vector.
				SortingFuncForVector(temp->studentsAttendingIDs); // it sorts the member of function with non-increasing way.
			}
			//cout << courseCode << " " << courseName << " " << studentID << endl;
		}
		cout << "The linked list is created" << endl;

		cout << "The inital list is:" << endl;

		DisplayList(head);

		cout << endl;

		while(userChoice != 4) // until users want to terminate code, it will take choice from user to do certain functions.
		{
			TakingChoice(userChoice);
			if(userChoice == 1) // It will add new lessons or ID's into linked list.
			{
				cout << "Give the student ID and the course names and course codes that he/she wants to add:" << endl;
				cin >> s;
				courseCode = s;
				getline(cin,a); // it is a usage of getline by taking input from user
				
				istringstream input2(a); // it returns line into istringstream structure.
				
				while(input2 >> word) // until it reaches the end of the line it takes word one by one
				{
					if(NumberChecker(word.substr(0,1))) // it checks that the taken word is number which refers the student id.
					{
						intStudentID = atoi(word); // it returns string that is all number into integer by using 
						if((lessonCheckerInList(head, courseCode))) // it checks certain course in the linked list.
						{
							head = AddNewLesson(head, courseName, courseCode, intStudentID); // if it is not in linked list, it creates node and add it
							cout << courseCode << " does not exist in the list of Courses. It is added up."<< endl;
							cout << "Student with id " << intStudentID << " is enrolled to " << courseCode << endl;
						}
						else
						{
							courseNode *temp2 = head; // if course in the linked list it will search it by temp2 pointer.
							while(temp2->courseCode != courseCode)
							{
								temp2 = temp2->next;
							}
							if((SameIdCheckerInCourse(temp2->studentsAttendingIDs,intStudentID)))
							{
								temp2->studentsAttendingIDs.push_back(intStudentID);
								SortingFuncForVector(temp2->studentsAttendingIDs);
								cout << "Student with id " << intStudentID << " is enrolled to " << courseCode << endl;
							}
							else
							{
								cout << "Student with id " << intStudentID << " already is enrolled to " << courseCode << ". No action taken." << endl;
							}
						}
					}
					else if(NumberChecker(word.substr(word.length()-1,1)))
					{
						courseCode = word;
					}
					else
					{
						courseName = word;
					}
				}
			//DisplayList(head);	
			}
			else if(userChoice == 2)
			{
				cout << "Give the student ID and the course names and course codes that he/she wants to drop:" << endl;
				cin >> s;
				courseCode = s;
				getline(cin,a); // it is a usage of getline by taking input from user
				istringstream input3(a);
				
				while(input3 >> word) // until it reaches the end of the line it takes word one by one
				{
					if(NumberChecker(word.substr(0,1))) // it checks that the taken word is number which refers the student id.
					{
						intStudentID = atoi(word); // it returns string that is all number into integer by using 
						if(!(lessonCheckerInList(head, courseCode))) // It looks for the course in the list or not.
						{
							courseNode *temp3 = head; 
							while(temp3->courseCode != courseCode) // if it is in the linked list, it searches for the position by using another pointer.
							{
								temp3 = temp3->next;
							}
							if((SameIdCheckerInCourse(temp3->studentsAttendingIDs,intStudentID))) // it checks the id in the list if not it shows the student did not enroll the course so he/she cannot drop
							{
								cout << "Student with id " << intStudentID << " is not enrolled to " << courseCode << ", thus  he can't drop that course." << endl;
							}
							else
							{
								SwapWithLastElementOfVector(temp3->studentsAttendingIDs, intStudentID); // it carries the id to the end of the vector to use pop_back()
								temp3->studentsAttendingIDs.pop_back(); // it deletes the end of the vector
								SortingFuncForVector(temp3->studentsAttendingIDs); // it sorts again the vector values in non-decreasing order.
								cout << "Student with id " << intStudentID << " has dropped " << courseCode << endl; 
							}
						}
						else
						{
							cout << "The " << courseCode << " course is not in the list, thus student with id " << intStudentID << " can't be dropped" << endl; // this course was not saved on database.
						}
					}
					else if(NumberChecker(word.substr(word.length()-1,1))) // course codes last characters is number so it finds the course code.
					{
						courseCode = word;
					}
					else
					{
						courseName = word;
					}
				}
			//DisplayList(head);
			}
			else if(userChoice == 3)
			{
				cout << "The current list of course and the students attending them:" << endl;
				DisplayList(head);
			}
		}
		if(userChoice == 4) // it is for displaying course situation after add-drop period.
			{
				cout << "The add/drop period is finished. Printing the final list of courses and students attending them." << endl;
				cout << "NOTE: Courses with less than 3 students will be closed this semester." << endl;
				FinalDisplayList(head);
				DeleteList(head); // deleting linked list
				delete head; // deleting head pointer for linked list.
			}
	}
	inputFile.close();
	return 0;
}
