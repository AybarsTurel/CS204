/*************
Purpose: This program is a simple example of Minesweeper game.
Usage: There are no .txt files that are used in the program. However, the program need randgen.h and randgen.cpp file to be executed.
Author: Sevki Aybars Turel 28238
Date: 10/9/2021
Any known bugs: When user creates 1*1 matrix, game will not be created. Additionally, program did not check matrix size is whether postive or not. 
References: randgen.h and randgen.cpp file has been taken from CS204 Recitation Materials. Additionally, Print function has taken from CS204 Recitation Materials but it has been updated according to new need in the program.
**************/

#include <iostream>
#include <string>
#include <vector>
#include "randgen.h"
#include <iomanip>

using namespace std;

bool checkCoordinates(const int& y, const int& x, const int& row, const int& column)  // In this function, coordinates that are taken from users has been checked in order to decide coordinates are in the range of matrix.
{
	if(x >= column || y >= row) 
	{
		return true; // If x (that represents the coordinate for x-axis) and y (that represents the coordinate for y-axis) in the matrix size, function will return true to approve the validation of coordinates.
	}
	return false;
}

void takingCoordinates(int & y, int & x,  const int& row, const int& column)
{
		cout << "Give the coordinates: ";

			cin >> y >> x;

			while(checkCoordinates(y, x, row, column)) // check for valid coordinates
			{
				cout << "It is out of range. Please give a valid coordinates: ";
				cin >> y >> x;
			}
}


void takeChoice(string & choice) // It is a simple input function to take users' choice. 
{
	cout << "Press:" << endl;
	cout << "1. If you want to find out the surrounding of a cell" << endl;
	cout << "2. If you want to open the cell" << endl;
	cout << "3. If you want to exit" << endl;
	cin >> choice;
}

void minesweeperGameMatrixGenerator(vector<int> & xCoordinatesOfBombs, vector <int> &yCoordinatesOfBombs, const int & nrMines, const int & column ,const int row, vector<vector<int>> & mat )
{
	/*
	In this function, randomly created x and y coordinates are stored in seperate vectors that store the coordinates of bomb. 
	The program will scan the boxes around bomb,if any, and add 1 value to each box adjacent to the bomb that does not contain any bomb.
	Mat matrix will be game matrix that includes bombs and numbers.
	*/

	RandGen rand;

	bool notSame = true;
	int numCoordinatesOfBombs = 0;

	while(numCoordinatesOfBombs < nrMines) // In this loop, until we get nrMines bombs, loop takes random number and check it is unique coordinates or not. 
	{
		int yCoordinate = rand.RandInt(0,row-1);
		int xCoordinate = rand.RandInt(0,column-1);
		notSame = true;
		for(int i = 0; i < xCoordinatesOfBombs.size() && notSame == true ; i++) // Loop will take every x and y to check whether is unique coordinates or not.
		{
			if((xCoordinatesOfBombs[i] == xCoordinate) && (yCoordinatesOfBombs[i] == yCoordinate ))
			{
				notSame = false;
			}
		}
		if(notSame == true) // If the new coordinate is unique, it will be added coordinates vector.
		{
			xCoordinatesOfBombs.push_back(xCoordinate);

			yCoordinatesOfBombs.push_back(yCoordinate);

			numCoordinatesOfBombs++;	
		}
	}

	for(int i = 0; i < xCoordinatesOfBombs.size(); i++)
	{
		mat[yCoordinatesOfBombs[i]][xCoordinatesOfBombs[i]] = 66; 
		// In ASCII Characters, 66 represents 'B'. 
		// Bombs will be stored in matrix as 66 and it will convert 'B' while printing matrix.
	}
	for(int i = 0; i < xCoordinatesOfBombs.size(); i++) // In this loop, program will find the location of bombs. 
		//After that, the bombs are located in matrix, +1 value is added to the right-left boxes, bottom-upper boxes and cross boxes of the tile where the bomb is located.  
	{
		if(yCoordinatesOfBombs[i] + 1 <= (row-1) && mat[yCoordinatesOfBombs[i] + 1][xCoordinatesOfBombs[i]] != 66)
		{
			// In here, program checks there is a box under the box with bomb and if there is a bomb in this box. 
			// If there is a box without bomb under bomb, program will add +1 value to represent the number of bomb.
			mat[yCoordinatesOfBombs[i] + 1][xCoordinatesOfBombs[i]] +=1;
		}
		if((yCoordinatesOfBombs[i] - 1 >= 0) && mat[yCoordinatesOfBombs[i] - 1][xCoordinatesOfBombs[i]] != 66)
		{
			// In here, program checks there is a box on the box with bomb and if there is a bomb in this box. 
			// If there is a box without bomb on bomb, program will add +1 value to represent the number of bomb.
			mat[yCoordinatesOfBombs[i] - 1][xCoordinatesOfBombs[i]] +=1;
		}
		if(xCoordinatesOfBombs[i] + 1 <= (column - 1) && mat[yCoordinatesOfBombs[i]][xCoordinatesOfBombs[i] + 1] != 66)
		{
			// In here, program checks there is a box to the right of the box with bomb and if there is a bomb in this box. 
			// If there is a box without bomb to the right of bomb, program will add +1 value to represent the number of bomb.
			mat[yCoordinatesOfBombs[i]][xCoordinatesOfBombs[i] + 1] +=1;
		}
		if((xCoordinatesOfBombs[i] - 1 >= 0) && mat[yCoordinatesOfBombs[i]][xCoordinatesOfBombs[i] - 1] != 66)
		{
            // In here, program checks there is a box to the left of the box with bomb and if there is a bomb in this box. 
			// If there is a box without bomb to the left of bomb, program will add +1 value to represent the number of bomb.
			mat[yCoordinatesOfBombs[i]][xCoordinatesOfBombs[i] - 1] +=1;
		}

			// In these four if statements, it checks if there are boxes on the crosses of the box with the bomb 
			//and adds the value +1 to the cross boxes that do not include bombs.
		if((yCoordinatesOfBombs[i] + 1 <= (row-1) && xCoordinatesOfBombs[i] + 1 <= (column - 1)) &&  mat[yCoordinatesOfBombs[i] + 1][xCoordinatesOfBombs[i] + 1] != 66)
		{
			mat[yCoordinatesOfBombs[i] + 1][xCoordinatesOfBombs[i] + 1] +=1;
		}
		if((yCoordinatesOfBombs[i] + 1 <= (row-1) && xCoordinatesOfBombs[i] - 1 >=(0)) &&  mat[yCoordinatesOfBombs[i] + 1][xCoordinatesOfBombs[i] - 1] != 66)
		{
			mat[yCoordinatesOfBombs[i] + 1][xCoordinatesOfBombs[i] - 1] +=1;
		}
		if((yCoordinatesOfBombs[i] - 1 >= (0) && xCoordinatesOfBombs[i] + 1 <=(column - 1)) &&  mat[yCoordinatesOfBombs[i] - 1][xCoordinatesOfBombs[i] + 1] != 66)
		{
			mat[yCoordinatesOfBombs[i] - 1][xCoordinatesOfBombs[i] + 1] +=1;
		}
		if((yCoordinatesOfBombs[i] - 1 >= (0) && xCoordinatesOfBombs[i] - 1 >= (0)) &&  mat[yCoordinatesOfBombs[i] - 1][xCoordinatesOfBombs[i] - 1] != 66)
		{
			mat[yCoordinatesOfBombs[i] - 1][xCoordinatesOfBombs[i] - 1] +=1;
		}
	}	
}

void checkSurroundingForParticularBox(int x,int y, int row, int column, int & surroundingBomb,  vector<vector<int>> & mat)
{       //In this function, if user choose bomb location for surrounding, function will check right-left, up-down and cross boxes that includes bombs and store in surroundingBomb. This variable will display in surrounding function.
		surroundingBomb = 0;
		if(y + 1 <= (row-1) && mat[y + 1][x] == 66)
		{
			// In here, program checks there is a box under the box with bomb and if there is a bomb in this box. 
			// If there is a box without bomb under bomb, program will add +1 value to represent the number of bomb.
			surroundingBomb +=1;
		}
		if((y - 1 >= 0) && mat[y - 1][x] == 66)
		{
			// In here, program checks there is a box on the box with bomb and if there is a bomb in this box. 
			// If there is a box without bomb on bomb, program will add +1 value to represent the number of bomb.
			surroundingBomb+=1;
		}
		if(x + 1 <= (column - 1) && mat[y][x + 1] == 66)
		{
			// In here, program checks there is a box to the right of the box with bomb and if there is a bomb in this box. 
			// If there is a box without bomb to the right of bomb, program will add +1 value to represent the number of bomb.
			surroundingBomb+=1;
		}
		if((x - 1 >= 0) && mat[y][x - 1] == 66)
		{
            // In here, program checks there is a box to the left of the box with bomb and if there is a bomb in this box. 
			// If there is a box without bomb to the left of bomb, program will add +1 value to represent the number of bomb.
			surroundingBomb+=1;
		}
			// In these four if statements, it checks if there are boxes on the crosses of the box with the bomb 
			//and adds the value +1 to the cross boxes that do not include bombs.
		if((y + 1 <= (row-1) && x + 1 <= (column - 1)) &&  mat[y + 1][x + 1] == 66)
		{
			surroundingBomb+=1;
		}
		if((y + 1 <= (row-1) && x - 1 >=(0)) &&  mat[y + 1][x - 1] == 66)
		{
			surroundingBomb+=1;
		}
		if((y - 1 >= (0) && x + 1 <=(column - 1)) &&  mat[y - 1][x + 1] == 66)
		{
			surroundingBomb+=1;
		}
		if((y - 1 >= (0) && x - 1 >= (0)) &&  mat[y - 1][x - 1] == 66)
		{
			surroundingBomb+=1;
		}
}


void PrintWholeGameMatrix(const vector<vector<int>> & mat) // It is a simple print function. 
{ // This function will be used to display the whole matrix that was created at the beginning of the program with bombs and numbers. 
//In this program minesweeperGameMatrix will be displayed. minesweeperGameMatrix includes all the value for the game.
    for (int j=0; j < mat.size(); j++)
    {   
		for (int k=0; k < mat[0].size(); k++)
		{   
			if(mat[j][k] == 66) // In here, Program check the given box includes bomb or not. If includes bomb it will print char(66) that represents 'B'
			{
				cout << setw(4) << char(mat[j][k]);
			}
			else
			{
				cout << setw(4) << (mat[j][k]);
			}
        }
        cout << endl;
    }
}

void PrintMatrixWithOpeningBoxes(const vector<vector<int>> & mat) // It is an another print function to display game with 'X's. 
{//This function will take matrix that includes opened boxes by users and unopened boxes which are represented 'X'.
    for (int j=0; j < mat.size(); j++)
    {   
		for (int k=0; k < mat[0].size(); k++)
		{   
			if(mat[j][k] == 66 || mat[j][k] == 88)
			{
				cout << setw(4) << char(mat[j][k]);
			}
			else
			{
				cout << setw(4) << (mat[j][k]);
			}
        }
        cout << endl;
    }
}


void matrixGeneratorForOpeningCells(const vector<vector<int>> & mat1, vector<vector<int>> & mat2, const int & x, const int & y, bool & boomFound,int & number0fBoxesWithoutBomb)
{
	//This function will fill an empty matrix based on opened boxes.
	// mat1 represents the matrix that includes all information (bomb locations and numbers of bomb adjacent boxes) about game.
	// mat2 represents the empty vectors, this vector will be filled according to location that was opened by user.
	if( mat1[y][x] == 66)
	{
		mat2[y][x] = 66;
		boomFound = true;
	}
	else if( mat2[y][x] == 88) // this if statement is created for when the box opened the second this choice won't be counted.
	{
		mat2[y][x] = mat1[y][x];
		number0fBoxesWithoutBomb++; // this will use to understand the user has found the all boxes without bomb.
	}
}

void PrintForSurrounding(const vector<vector<int>> & mat,  const vector<vector<int>> & mat2, int x, int y, int surroundingBomb) // It is function that display the matrix for choice 1 (show surrounding).
{
	// Mat 1 represents the matrix that includes all information (bombs location and bomb numbers in adjacent boxes) about game.
	// Mat 2 represents the matrix that shows opened cells.
	// This for loop prints the choosen box from Mat1 to show how many bombs are there. After that it takes opened cells from mat2 to display the boxes that have already opened.
	// If there is a bomb where user look surrounding it will display bomb numbers at surroundings that were found in checkSurroundingForParticularBox function.
	// After it prints the closed box as 'X' with help of 88. char(88) == 'X'
	for (int j=0; j < mat.size(); j++)
    {   
		for (int k=0; k < mat[0].size(); k++)
		{   
			if( (j == y)  && (k == x))
			{
				if(mat[j][k] == 66)
				{
					cout << setw(4) << surroundingBomb;
				}
				else
				{
					cout << setw(4) << (mat[j][k]);
				}
				
			}
			else
			{
				if(mat2[j][k] == 88)
				{
					cout << setw(4) << char(mat2[j][k]);
				}
				else
				{
					cout << setw(4) << (mat2[j][k]);
				}
			}
        }
        cout << endl;
    }
	if(mat[y][x] == 66)
	{
		cout << "Around (" << y << "," << x << ") you have " << surroundingBomb << " bomb(s)" << endl;
	}
	else
	{
		cout << "Around (" << y << "," << x << ") you have " << mat[y][x] << " bomb(s)" << endl;
	}
}


int main()
{
	int row, column, x , y, nrMines, surroundingBomb;

	string choice;

	bool bombFound = false;

	cout << "Give the dimensions of the matrix: ";

	cin >> row >> column;
	
	cout << "How many bombs: ";
	
	cin >> nrMines;

	while((nrMines >= (row * column)) || (nrMines < 1)) // It is a simple check for number of mines.
	{
		if(nrMines >= (row * column))
		{
			cout << "The number of bombs can not be greater than the whole number of cells minus one. Please give the number of bombs again: ";
			cin >> nrMines;
		}
		else if(nrMines < 1)
		{
			cout << "The number of bombs could not be less than one. Please give the number of bombs again: ";
			cin >> nrMines;
		}
	}
	
	int number0fBoxesWithoutBomb = 0;
	
	vector<int> xCoordinatesOfBombs; // vector that stores numbers for x coordinates
	vector<int> yCoordinatesOfBombs; // vector that stores numbers for y coordinates
	vector<vector<int>> minesweeperGameMatrix(row, vector<int>(column)); // Matrix for the game that includes all information.
	vector<vector<int>> minesweeperMatrixForOpenningCells(row, vector<int>(column, 88)); // Matrix will includes opened cells. All boxes in matrix includes 88 to show closed boxes with 'X'in print function.  
	minesweeperGameMatrixGenerator(xCoordinatesOfBombs, yCoordinatesOfBombs, nrMines, column, row, minesweeperGameMatrix);
	
    //PrintWholeGameMatrix(minesweeperGameMatrix);
	cout << endl << endl;
	PrintMatrixWithOpeningBoxes(minesweeperMatrixForOpenningCells);
	cout << endl << endl;
	takeChoice(choice);

	while(choice != "3" && bombFound == false && number0fBoxesWithoutBomb != ((column*row) - nrMines))
	{

		if(choice == "1")
		{
			takingCoordinates(y, x, row, column);

			cout << endl << endl;

			checkSurroundingForParticularBox(x, y, row, column, surroundingBomb, minesweeperGameMatrix);

			cout << "Displaying the surrounding of (" << y << ","<< x << ") :" << endl;

			PrintForSurrounding(minesweeperGameMatrix, minesweeperMatrixForOpenningCells,x,y, surroundingBomb);

			takeChoice(choice);
			
		}
		else if(choice == "2")
		{
			takingCoordinates(y, x, row, column);

			cout << endl;

			matrixGeneratorForOpeningCells(minesweeperGameMatrix,  minesweeperMatrixForOpenningCells, x, y, bombFound, number0fBoxesWithoutBomb);
			
			cout << endl << endl;
			cout << "Openning cell (" << y << "," << x << ") :" << endl << endl;

			PrintMatrixWithOpeningBoxes(minesweeperMatrixForOpenningCells);

			if((bombFound == false) && (number0fBoxesWithoutBomb != ((column*row) - nrMines))) // It continue taking choice if bomb is not found and there are still boxes without bomb.
			{
				takeChoice(choice);
			}	
		}
		else
		{
			cout << "Your input is wrong. Please select one of the options: 1, 2 or 3." << endl;
			cin >> choice;
		}	
	}
	if(choice == "3") // this if statements checks that user want to terminate the game.
	{
		cout << "Program exiting . . ." << endl;
	}
	else if(bombFound == true) // this if statement chekcs that the user found any bomb in opening cells function.
	{
		cout << endl << endl;
		cout << "Unfortunately, you stepped on a mine" << endl;
		cout << endl;
		cout << "Arrengment of mines:" << endl << endl;
		PrintWholeGameMatrix(minesweeperGameMatrix);
		cout << endl << endl;
		cout << ">>>>> Game Over! <<<<<"<< endl;
	}
	else if(number0fBoxesWithoutBomb == ((column*row) - nrMines)) // this if statement checks that user found all the boxes without bombs and win the game.
	{
		cout << "Congratulations! All the non-mined cells opened successfully" << endl;
		cout << endl;
		cout << "You won!";
		cout << endl << endl;
		cout << ">>>>> Game Over! <<<<<"<< endl;
	}
	return 0;	
}