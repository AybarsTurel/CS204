/*************
Purpose: This code was writen to store information of bus line and bus stops with linked lists. Additionally, this data will be used to make simple operations in buslines such as adding lines or stops, deleting lines or stops and find the routes to travel. 
Usage: There is a .txt file that name is busLines.txt. In this file, program gets initial data about bus lines and buses' stops. In this program, there is no additional files. 
Author: Sevki Aybars Turel 28238
Date: 07/11/2021
Any known bugs: There is a bug in option 3 adding bus stop because when user put wrong input, code asks again to give valid input otherwise you can use 0 to go back to main menu. However, 0 is also used for the adding bus stop into first element of linked list. Program will add bus stop at worst the begining of the list instead of going to back.
References: There is no additional file that are used in this code. Structs and main functions were taken from homework file.
**************/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct busStop //The structs that stores stop information of a certain line
{
	string busStopName;
	busStop *left;
	busStop *right;
	busStop::busStop()
	{}

	busStop::busStop (const string & a, busStop* b, busStop* c)
		: busStopName(a), left(b), right(c)
	{}

}; 
struct busLine  //The structs that stores line information.
{
	string busLineName;
	busLine *next;
	busStop *busStops;

	busLine::busLine()
	{}

	busLine::busLine (const string & a, busLine* b, busStop* c)
		: busLineName(a), next(b), busStops(c)
	{}
	

};

busLine *head = nullptr; // This is a pointer global variable that points the head of linked list.

busLine *CreateBusLine(busLine * head, string busStopName, string firstStopBus) // This functions creates a list of bus lines with the first stop information.
{
	busLine *  ptr = head; 
	if(head == nullptr)
	{
		busLine * temp = new busLine;  //node to be inserted
		busStop * temp2 = new busStop(firstStopBus, NULL, NULL);
		temp->busLineName = busStopName;
		temp->busStops = temp2;
		temp-> next = head; //connect the rest
		return temp;
	}
	while (ptr->next != nullptr)
    {   
		ptr = ptr->next;
    } 
	busLine * temp = new busLine;  //node to be inserted 
	busStop * temp2 = new busStop(firstStopBus, NULL, NULL);
	temp->busLineName = busStopName;
	temp->busStops = temp2;
	temp->next = ptr->next; //connect the rest
	ptr->next = temp;

    return head;
} 

busLine *CreateBusStop(busLine * head, string busStop1, string busLineName) // This function add new bus stops to a certain line.
{
	busLine *  ptr = head;
	while((ptr != NULL) && (ptr->busLineName != busLineName))
	{
		ptr = ptr->next;
	}
	busStop* temp = ptr->busStops;
	
	while(temp->right != NULL)
	{
		temp = temp->right;
	}
	busStop* newNode = new busStop(busStop1,temp,NULL);
	temp->right = newNode;
	return head;
}

void DeleteList(busLine* newLine) // This function is simply deletes the nodes in the linked list that includes bus stops.
{
	busStop * temp = newLine->busStops;
	busStop * temp2 = new busStop;
	while (temp != NULL)
	{
		temp2 = temp->right;
		delete temp;
		temp = temp2;
	}
	delete temp2;
}

bool consistencyCheck() // This function were taken from homework file to determine that there is any inconsistency in linked list.
{
	busLine* currBL = head; //a global variable
	while(currBL) 
	{
		busStop* currBS = currBL->busStops;
		while(currBS) 
		{
			busStop* rightBS = currBS->right;
			if(rightBS && rightBS->left != currBS) 
			{
				cout << "Inconsistency for " << currBL->busLineName << " " << currBS->busStopName << endl;
				return false;
			}
			currBS = currBS->right;
		}
		currBL = currBL->next;
	}
	return true;
} 

void PrintBusLines() // It is a simple function that prints the information that were collected in a linked list.
{
	busLine *ptr = head;
	while(ptr != NULL)
	{
		cout << ptr->busLineName << ":";
		busStop* temp = ptr->busStops;
		while(temp != NULL)
		{
			if(temp->right != NULL)
			{
				cout << temp->busStopName << " <-> ";
				temp = temp->right;
			}
			else
			{
				cout << temp->busStopName;
				temp = temp->right;
			}
		}
		ptr = ptr->next;
		cout << endl;
	}
}

void printMainMenu() // This function was taken from the homework file to present options for users.
{
	cout << endl;
	cout <<"I***********************************************I"<<endl
	<<"I 0 - EXIT PROGRAM I"<<endl
	<<"I 1 - PRINT LINES I"<<endl
	<<"I 2 - ADD BUS LINE I"<<endl
	<<"I 3 - ADD BUS STOP I"<<endl
	<<"I 4 - DELETE BUS LINE I"<<endl
	<<"I 5 - DELETE BUS STOP I"<<endl
	<<"I 6 - PATH FINDER I"<<endl
	<<"I***********************************************I"<<endl
	<<">>";
	cout << endl;
}

bool CheckerSameBusLine(string word) // This function checks whether a certain line is already in a linked list.
{
	busLine *ptr = head;
	while(ptr != NULL)
	{
		if(ptr->busLineName == word) // If a certain line is in the linked list it will be turn false.
		{
			return false;
		}
		ptr = ptr->next;
	}
	return true;
}

bool CheckerSameBusStopsLine(string word, busLine*newLine) // This function checks a bus stop is already in the line or not.
{
	busLine *ptr = newLine;
	busStop *temp = ptr->busStops;
	while(temp != NULL)
	{
		if(temp->busStopName == word) // If a certain bus stop is in the linked list it will be turn true.
		{
			return true;
		}
		else
		{
			temp = temp->right;
		}
	}
	return false;

}

void PrintFuncForAList(busLine*newLine) // It is a simple print function to print just a bus line with its stops.
{
	busStop * temp = newLine->busStops;
	cout << newLine->busLineName << ":";
	while(temp != NULL)
	{
		if(temp->right != NULL)
		{
			cout << temp->busStopName << "<->";
			temp = temp->right;
		}
		else
		{
			cout << temp->busStopName;
			temp = temp->right;
		}
	}

}

void AddBusLine() // It adds a new line at the begininbg of the whole list.
{
	int size = 0;
	string input, choice;
	cout << "Enter the name of the new bus line (0 for exit to main menu)." << endl;
	cin >> input;
	while(input != "0")
	{
		while(!(CheckerSameBusLine(input))) // In here, until the code gets a valid line that is not in the linked list, it will ask for a line that is unique.
		{
			cout << "Bus line already exists: enter a new one (0 for exit):" << endl;
			cin >> input;
		}
		busStop * busStops = new busStop("",NULL,NULL);
		busLine * newBusLine = new busLine(input, NULL, busStops);
		if(input != "0")
		{
			cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
			cin >> input;
		}
		while(input != "0")
		{
			if(CheckerSameBusStopsLine(input,newBusLine)) // In here, code checks the bus stop is in the line or not. Until it get an unique bus stop, it will ask.
			{
				cout << "Bus stop already exists in the line" << endl;
				cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
				cin >> input;
			}
			else
			{
				busStop * temp = busStops;
				while(temp->right != NULL)
				{
					temp = temp->right;
				}
				if(temp->busStopName == "")
				{
					temp->busStopName = input;
					cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
					cin >> input;
					size++; // if new bus stop is added to a line, it will count how many bus stop was added.
				}
				else
				{
					busStop* newNode = new busStop(input,temp,NULL);
					temp->right = newNode;
					cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
					cin >> input;
					size++; // if new bus stop is added to a line, it will count how many bus stop was added.
				}
			}
		}
		if(size != 0) // In here, if a new line is an empty one it will not be added to a linked list.
		{
			cout << "The bus line information is shown below" << endl;
			PrintFuncForAList(newBusLine);
			cout << endl;
			cout << "Are you sure? Enter (y/Y) for yes (n/N) for no?" << endl;
			cin >> choice;
			if(choice == "Y" || choice == "y")
			{
				busLine * headTemp = head;
				newBusLine->next = headTemp;
				head = newBusLine;
				PrintBusLines();
			}
			else if(choice == "N" || choice == "n")
			{
				DeleteList(newBusLine); // In here, code deletes the a new bus line because user did not prefer to add.
			}
		}
		else if(size == 0 && input == "0")
		{
			cout << "You are not allowed to add an empty bus line" << endl;
		}
	}

}

void AddBusStop() // It adds new bus stops to desired line.
{
	string busLineName, newStopName, stopLocation;
	cout << "Enter the name of the bus line to insert a new bus stop (0 for main menu)" << endl;
	cin >> busLineName;
	if((CheckerSameBusLine(busLineName)) && busLineName != "0") // It checkes th line that will be include new bu stop in the list or not
	{
		cout << "Bus line cannot be found. Going back to previous menu." << endl;
	}
	else if(busLineName == "0")
	{
		cout << "Going back to previous menu" << endl;
	}
	else
	{
		busLine *temp = head;
		while(temp->busLineName != busLineName)
		{
			temp = temp->next;
		}
		cout << "The bus line information is shown below" << endl;
		PrintFuncForAList(temp);
		cout << endl;
		cout << "Enter the name of the new bus stop" << endl;
		cin >> newStopName;
		if(CheckerSameBusStopsLine(newStopName,temp)) // It checks that desired bus stop is in the line or not.
		{
			cout << "Bus stop already exists. Going back to previous menu." << endl;
		}
		else
		{
			cout << "Enter the name of the previous bus stop to put the new one after it (0 to put the new one as the first bus stop)" << endl;
			cin >> stopLocation;
			while(stopLocation != "0" && (!(CheckerSameBusStopsLine(stopLocation,temp))))
			{
				cout << "Bus stop does not exist. Typo? Enter again (0 for main menu)" << endl;
				cin >> stopLocation;

			}
			if(stopLocation == "0") // Adding to the beggining of the bus stops
			{
				busStop *newStop = new busStop(newStopName,NULL,temp->busStops);
				busStop *oldStop = temp->busStops;
				temp->busStops = newStop;
				oldStop->left = newStop;
				PrintFuncForAList(temp);
			}
			else // adding  the bus stops
			{
				busStop*temp2 = temp->busStops;
				while((temp2->busStopName) != stopLocation)
				{
					temp2 = temp2->right;
				}
				if(temp2 ->right == NULL) // It adds bus stops to last elemet of linked list
				{
					busStop *newStop = new busStop(newStopName,temp2,NULL);
					temp2->right = newStop;
					PrintFuncForAList(temp);
				}
				else // It ass bus stop to the middle of the list.
				{
					busStop *newStop = new busStop(newStopName,temp2,temp2->right);
					temp2->right = newStop;
					temp2 = temp2->right->right;
					temp2->left = newStop;
					PrintBusLines();
				}
			}
			
		}

	}

}

void DeleteBusLine() // It deletes line that was prefered by user.
{
	string deletedBusLine;
	cout << "Enter the name of the bus line to delete" << endl;
	cin >> deletedBusLine;
	if(CheckerSameBusLine(deletedBusLine))
	{
		cout << "Bus line cannot be found. Going back to previous (main) menu." << endl;
	}
	else
	{
		busLine *ptr = head;
		if(ptr->busLineName == deletedBusLine) // If line that will be deleted at the beginning of the head, it deletes and updates head.
		{
			head = ptr->next;
			DeleteList(ptr);
		}
		else
		{
			while(ptr->next->busLineName != deletedBusLine)
			{
				ptr = ptr->next;
			}
			if(ptr->next == NULL) // If line that will be deleted at the last element of the linked list, it deletes.
			{
				busLine *temp = ptr->next;
				temp = ptr->next;
				DeleteList(temp);
				ptr->next = NULL;
			}
			else // It deletes the line that is at the middle of the linked list.
			{			
				busLine *temp = ptr->next;
				ptr->next = ptr->next->next;
				DeleteList(temp);
			}
		}
		PrintBusLines();
	}
}

void DeleteBusStop() // This function deletes a stop from a certain line.
{
	busLine * temp = head;
	busLine * temp3 = head;
	string busLine, deletedStop;
	cout << "Enter the name of the bus line to delete a new bus stop (0 for main menu)" << endl;
	cin >> busLine;
	if(!(CheckerSameBusLine(busLine)))
	{
		while(temp->busLineName != busLine)
		{
			temp = temp->next;
		}
		cout << "The bus line information is shown below" << endl;
		PrintFuncForAList(temp);
		cout << endl;
		cout << "Enter the name of the bus stop to delete (0 for main menu)" << endl;
		cin >> deletedStop;
		while(deletedStop != "0" && (!(CheckerSameBusStopsLine(deletedStop,temp))))
		{
			cout << "Bus stop cannot be found. Enter the name of the bus stop to delete (0 for main menu)" << endl;
			cin >> deletedStop;
		}
		if(deletedStop != "0")
		{
			busStop *temp2 = temp->busStops;
			while(temp2->busStopName != deletedStop)
			{
				temp2 = temp2->right;
			}
			if(temp2->right == NULL)
			{
				if(temp2->left != NULL) // It is the only element in the linked list so list will be deleted
				{
					temp2->left->right = NULL;
					delete temp2;
					PrintBusLines();
				}
				else
				{
					if(temp->next == NULL) // It deletes last element of the linked list.
					{
						while(temp3->next != temp)
						{
							temp3 = temp3->next;
						}
						temp3->next = NULL;
						DeleteList(temp);
					}
					else if(temp == head) //It deletes the begining of the linked list.
					{
						head = temp->next;
						DeleteList(temp);
					}
					else // It deletes the middle of the list.
					{
						while(temp3->next != temp)
						{
							temp3 = temp3->next;
						}
						temp3->next = temp->next;
						DeleteList(temp);
					}
					PrintBusLines();
				}
			}
			else if(temp2->left == NULL)
			{
				temp->busStops = temp2->right;
				temp2->right->left = NULL;
				delete temp2;
				PrintBusLines();
			}
			else
			{
				temp2->left->right = temp2->right;
				temp2->right->left = temp2->left;
				delete temp2;
				PrintBusLines();
			}
		}
	}
	else
	{
		cout << "Bus line cannot be found. Going back to previous (main) menu." << endl;
	}
}

void PathFinder()
{
	string locationNow,locationGo;
	bool inTheLine = false;
	bool foundLocation = false;
	bool inGo = false;
	bool inNow = false;
	string whichSideHasLloc = "";
	cout << "Where are you now?" << endl;
	cin >> locationNow;
	cout << "Where do you want to go?" << endl;
	cin >> locationGo;
	busLine *temp = head;
	busLine *temp2 = head;
	string left = ""; // This string includes the bus stops when list executed to left
	string right = ""; // This string includes the bus stops when list executed to right
	while(temp != NULL && inTheLine == false)
	{
		if(CheckerSameBusStopsLine(locationGo,temp) && CheckerSameBusStopsLine(locationNow,temp)) // Here checks the location that wanted to go and the location that were been in the list or not.
		{
			inTheLine = true;
		}
		else
		{
			temp = temp->next;
		}
	}
	if(inTheLine) // if both location in th same line it starts to search for the route.
	{
		busStop *busStopGo = temp->busStops;
		while(busStopGo->busStopName != locationNow)
		{
			busStopGo = busStopGo->right;
		}
		busStop *temp1 = busStopGo; 
		while(temp1 != NULL && foundLocation == false && temp1->busStopName != locationGo ) // this function tried to find the location that wanted to be in left of the "now" location
		{
			left = left + temp1->busStopName + "->";
			temp1 = temp1->left;
			if((temp1 != NULL) && temp1->busStopName == locationGo)
			{
				foundLocation = true; // It turns true when it founds to location that wanted to go.
				whichSideHasLloc = "left"; // It simply represents the location of the stop according to current location.
			}

		}
		while(busStopGo != NULL && foundLocation == false && busStopGo->busStopName != locationGo ) // this function tried to find the location that wanted to be in right of the "now" location
		{
			right = right + busStopGo->busStopName + "->";
			busStopGo = busStopGo->right;
			if((busStopGo != NULL) && busStopGo->busStopName == locationGo)
			{
				foundLocation = true; // It turns true when it founds to location that wanted to go.
				whichSideHasLloc = "right";// It simply represents the location of the stop according to current location.
			}
		}
		left = left + locationGo;
		right = right + locationGo;
		if(whichSideHasLloc == "right")
		{
			cout << "You can go there by " << temp->busLineName << ": ";
			cout << right << endl;
		}
		else
		{
			cout << "You can go there by " << temp->busLineName << ": ";
			cout << left << endl;
		}

	}
	else
	{
		while(temp2 != NULL)
		{
			if(CheckerSameBusStopsLine(locationGo,temp2))
			{
				inGo = true;
			}
			if(CheckerSameBusStopsLine(locationNow,temp2))
			{
				inNow = true;
			}
			temp2= temp2->next;
		}
		if(inGo == false || inNow == false) // One of the locations is not in the whole list.
		{
			cout << "Bus stop does not exist in the table. Going back to previous menu." << endl;
		}
		else
		{
			cout << "Sorry no path from "<< locationNow << " to " << locationGo << " could be found." << endl;
		}
			
	}
}

void processMainMenu() // This function was taken from homework documents. It decides the functions that will be implemented.
{
	char input;
	do
	{
		if(!consistencyCheck()) 
		{
			cout << "There are inconsistencies. Exit." << endl;
			return;
		}
		printMainMenu();
		cout << "Please enter your option " << endl;
		cin >> input;
		switch (input) 
		{
			case '0':
				cout << "Thanks for using our program" << endl;
				return;
			case '1':
			PrintBusLines();
				break;
				case '2':
			AddBusLine();
				break;
				case '3':
			AddBusStop();
				break;
				case '4':
			DeleteBusLine();
				break;
				case '5':
			DeleteBusStop();
				break;
				case '6':
			PathFinder();
				break;
				default:
					cout << "Invalid option: please enter again" << endl;
		} //switch
	}while(true);
}//processMainMenu

void DeleteAllElementInLinkedList() // It is a function that will delete every line with its bus stops to release the memory in the heap.
{
	busLine *tempForHead = new busLine;
	busStop *tempForBusStop = new busStop;
	busStop *tempForBusStop2 = new busStop;
	while(head != NULL)
	{
		tempForBusStop = head->busStops;
		while(tempForBusStop ->right != NULL) // This goes until the end of the bus stops lines
		{
			tempForBusStop = tempForBusStop->right;
		}
		while(tempForBusStop->left != NULL) // Here, code will delete every bus stops from the left side to right side.
		{
			tempForBusStop2 = tempForBusStop;
			tempForBusStop = tempForBusStop2->left;
			delete tempForBusStop2;
			
		}
		tempForHead = head->next;
		delete head;
		head = tempForHead;
	}
}


int main()
{
	string filename = "busLines.txt", line, word1, word2, busLineName;
	ifstream busLines;
	int size = 0;
	//busLine *head = nullptr;
	busLines.open(filename.c_str());
	if(!(busLines.fail()))
	{	
		while(getline(busLines,line))
		{
			istringstream inputLine(line);
			inputLine >> word1 >> word2;
			int index = word1.find(":");
			word1 = word1.substr(0,index);
			busLineName = word1;
			string firstBusStop = word2;
			head = CreateBusLine(head, busLineName, firstBusStop);
			while((inputLine >> word1) && (word1 != "\n"))
			{
				//cout << word1 << endl;
				head = CreateBusStop(head, word1, busLineName);
			}
		}
		processMainMenu();
		DeleteAllElementInLinkedList();	// It is a function that deletes every line one by one.
		//PrintBusLines();
	}
	else
	{
		cout << "Error: Cannot open file: " << filename << endl;
	}
	busLines.close();
	return 0;
}