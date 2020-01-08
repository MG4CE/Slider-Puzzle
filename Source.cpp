/*********************************************************************************************
File:    Source.cpp
Description (or purpose): 3x3 8 puzzle game, that uses and empty space to rearrange numbers to the correct postion
Name: Maged Mohammed
Date:  2017-06-02
Inputs:  int limit - user set limits
		 int choice - user choice to excute what they want
		 int move - based on the number moves the space to the corrsponding location
		 int order - lets the user choice how they can solve the puzzle

Outputs: to screen: Menu - Shows the user what the program can do
					Board - Shows the board puzzle that allows the user to play
					Solved State - Shows the user the correct state if needed

Functions: showSquare() - Updates the board when ever it's called with elements in the array, 
						  also adds a border around the numbers and replaces the 0 with and empty space
		   
		   reset() - Shuffles all the elements with in the 2d array using a built in C++ funtion, also resets
					 count for next game

		   check() - Checks for the correct order every time its called based on the ascending or decending order

		   menu() - Displays the menu to the user, takes in choice and checks if it is valid

		   checkZero() - check for the location of the empty space so it can be used else where

		   solved() - Displays solved state based on ascending or decending order

		   right() - moves 0 / empty space to the right and doesent preform the move if it's invalid
		   left() - moves 0 / empty space to the left and doesent preform the move if it's invalid
		   down() - moves 0 / empty space to the down and doesent preform the move if it's invalid
		   up() - moves 0 / empty space to the up and doesent preform the move if it's invalid
**********************************************************************************************/
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <time.h>
#include <windows.h>

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

using namespace std;

int const square = 3; //Global variable for all of the 2d array varibles

//Delcaring primary functions
void showSquare(int box[square][square], int order);
void reset(int box[square][square], int &count);
void check(int box[square][square], int count, bool &checkMe, int order);
void solved(int box[square][square], int order);
void menu(int &choice); 
void checkZero(int box[square][square], int &x, int &y);

//Movement functions
void left(int box[square][square], int x, int y);
void right(int box[square][square], int x, int y);
void up(int box[square][square], int x, int y);
void down(int box[square][square], int x, int y);

int main() {
	//Declaring Variables
	//Variable to count how many moves the user has preformed
	int count = 0; 
	//Sets a limit for count if the user wants to 0 = no limit
	int limit = 0;
	//Locatons for 0
	int x, y; 
	//Preintalized 2d array
	int box[square][square] = { 0,1,2,3,4,5,6,7,8 }; 
	//Stores users menu option
	int choice;
	//Stores users move lication
	char move;
	//Ascending or Decending option
	int order = 1;
	bool checkMe = false; //Varible to indcate if the puzzle is solved

	while (1 == 1)
	{
		//First do loop used for the menu screen
		do { 

			menu(choice); //Go to menu function

			checkMe = false; //Resets solved puzzle states to false

			//Swtich statement to do work with users option 
			switch (choice)
			{
			case 1: reset(box, count); //Go to reset funtion
				break;
			case 2: solved(box, order); cout << endl << endl;  system("pause"); //Shows solved state and waits for uset to press enter
				break;
			case 3: system("cls"); cout << "Enter a number limit: ";  cin >> limit; //If choice is 3 then user limit will be taken in
				break;
			case 4: system("cls"); cout <<"1. Ascending" << endl << "2. Descending" << endl << endl << "Enter order choice: "; cin >> order; // If choice is 4 user has to choose an order ascending or decending 
				break;
			case 5: return 0; //If choice is 5 the program will return 0 and close the console program
				break;
			}

			reset(box, count); //Go to reset function

			system("cls"); // Clears screen for next execution

			//If statement, to check if order input is valid, if not the program will go back to the menu
			if (order > 2)
			{
				cout << "Invalid Order!" << endl;
				system("pause");
				continue;
			}

		} while (choice != 1);

		// Do while loop for the game it self movement of the space
		do {
			system("cls");//Clears the screen (mainly for updating puzzle and reseting the screen)

			checkZero(box, x, y); //Checks where the space is

			check(box, count, checkMe, order); //Checks if the puzzle is solved

			//If rhe puzzle is solved the program will break out of the loop inform the user of their win and go back to the menu loop
			if (checkMe == true)
			{
				break; 
			}

			showSquare(box, order); //Shows the square with all the numbers in there place

			//Cout for movement options
			cout << setfill('-') << setw(22) << "-" << setfill(' ') << endl;
			SetConsoleTextAttribute(console, 14);
			cout << "Use WASD for Movement" << endl;
			cout << "9. Exit" << endl;
			SetConsoleTextAttribute(console, 15);
			cout << setfill('-') << setw(22) << "-" << setfill(' ') << endl;
			cin >> move; //Takes in move number

			//Switch statment to do work with move number
			switch (move)
			{
			case 'd': right(box, x, y); //Go to function right moves space to the right
				break;
			case 'a': left(box, x, y); //Go to function left moves space to the right
				break;
			case 'w': up(box, x, y); //Go to function up moves space to the right
				break;
			case 's': down(box, x, y); //Go to function down moves space to the right
				break;
			case '[': box[0][0] = 1; box[0][1] = 2; box[0][2] = 3; box[1][0] = 4; box[1][1] = 5; box[1][2] = 6; box[2][0] = 7; box[2][1] = 8; box[2][2] = 0; //Code to solve in ascending order *used for debuging*
				break;
			case ']': box[0][0] = 8; box[0][1] = 7; box[0][2] = 6; box[1][0] = 5; box[1][1] = 4; box[1][2] = 3; box[2][0] = 2; box[2][1] = 1; box[2][2] = 0; //Code to solve in decending order *used for debuging*
	 			break;
			case '9': cout << endl << "Moves: " << count << endl << endl; system("pause"); system("cls"); //If the user chooses 9 to exit the moves used will be shown and the program will pause until the user press a key
				break;
			} 

			//Checks if the choice is valid if not the program will go back to the start of the loop
			if ((move != '9') && (move != '[') && (move != ']') && (move != 'w') && (move != 'a') && (move != 's') && (move != 'd'))
			{
				cout << "Invalid option! Please choose again!" << endl << endl;
				system("pause");
				continue;
			}

			count++; //adds one for every move

			//If limit is 0 then there are no restrection set
			if (limit == 0)
			{
				continue;
			}

			//If limit is equal to count if it is the program will inform the user, pause and end the game
			else if (count == limit)
			{
				cout << "Move Limit Reached!" << endl;
				system("pause");
				system("cls");
				break;
			}
		} while (move != '9'); //Exits when the user choices the number 9
	}
	return 0;
}

void menu(int &choice)
{
	do {
		//Outs puts the menu and all the options
		cout << setfill('-') << setw(120) << "-" << setfill(' ');
		SetConsoleTextAttribute(console, 13);
		cout << right << setw(60) << "3x3 Puzzle" << endl;
		cout << "The objective of this game is to solve a 3x3 randomly generated puzzle in accending order from 1-8" << endl;
		cout << "The 0 in the puzzle will represent the empty space that can be moved" << endl;
		cout << "If the puzzle is unsolveable a reset option will be present and will give you the option to reset the puzzle" << endl;
		SetConsoleTextAttribute(console, 15);
		cout << setfill('-') << setw(120) << "-" << setfill(' ') << endl;
		SetConsoleTextAttribute(console, 11);
		cout << "1. Start" << endl;
		cout << endl;
		cout << "2. Show Solved State" << endl;
		cout << endl;
		cout << "3. Set Count Limit" << endl;
		cout << endl;
		cout << "4. Choose Order" << endl;
		cout << endl;
		cout << "5. Exit" << endl;
		SetConsoleTextAttribute(console, 15);
		
		//Takes in the choice 
		cin >> choice; 

		//If the choice is invalid over 5 it would inform the user and go back to the menu again
		if (choice > 5)
			{
			cout << "Invalid option! Please choose again!" << endl <<endl;
			system("pause");
			system("cls");
			continue;
			}
		//If the choice is valid the menu loop will break and the program will return back to int main
		else
			break;

	} while (1 == 1);
}
void solved(int box[square][square], int order)
{
	//Shows solved state in ascending order
	if (order == 1)
	{
		system("cls"); //Clears menu
		SetConsoleTextAttribute(console, 10); //changes color to green 
		cout << endl << endl << endl; //Down 3 lines
		cout << "\t\t " << setfill('-') << setw(13) << "-" << setfill(' ') << endl;
		cout << "\t\t" << " | " << 1 << " | " << 2 << " | " << 3 << " | " << endl;
		cout << "\t\t " << setfill('-') << setw(13) << "-" << setfill(' ') << endl;
		cout << "\t\t" << " | " << 4 << " | " << 5 << " | " << 6 << " | " << endl;
		cout << "\t\t " << setfill('-') << setw(13) << "-" << setfill(' ') << endl;
		cout << "\t\t" << " | " << 7 << " | " << 8 << " | " << " " << " | " << endl;
		cout << "\t\t " << setfill('-') << setw(13) << "-" << setfill(' ') << endl;
		cout << endl;
		SetConsoleTextAttribute(console, 15); //changes color back to white
	}
	//Shows solved state in decending order
	else
	{
		system("cls"); //Clears menu
		SetConsoleTextAttribute(console, 10); //Changes color to green
		cout << endl << endl << endl; //Down 3 lines
		cout << "\t \t" << " -------------" << endl;
		cout << "\t \t" << " | " << 8 << " | " << 7 << " | " << 6 << " | " << endl;
		cout << "\t \t" << " -------------" << endl;
		cout << "\t \t" << " | " << 5 << " | " << 4 << " | " << 3 << " | " << endl;
		cout << "\t \t" << " -------------" << endl;
		cout << "\t \t" << " | " << 2 << " | " << 1 << " | " << " " << " | " << endl;
		cout << "\t \t" << " -------------" << endl;
		cout << endl;
		SetConsoleTextAttribute(console, 15); //Change color back to white
	}
}
void reset(int box[square][square], int &count)
{
	count = 0; //resets the numbers of tries the user has attempted

	srand(time(NULL)); //Resets the randomize system time / seed so the numbers are diffrent everytime the program is started 
	random_shuffle(&box[0][0], &box[2][2]); //Shuffles the numbers with in the 2d array

}
void check(int box[square][square], int count, bool &checkMe, int order)
{
	//If the user is playing using the ascending gamemode then it would use the following if statement to check if the square is complete
	if (order == 1)
	{
		//Checks if the numbers are in order of 1,2,3,4,5,6,7,8,0 (complete square)
		if ((box[0][0] == 1) && (box[0][1] == 2) && (box[0][2] == 3) && (box[1][0] == 4) && (box[1][1] == 5) && (box[1][2] == 6) && (box[2][0] == 7) && (box[2][1] == 8) && (box[2][2] == 0))
		{
			//Shows the solved state box setup turns the square green (for corrsponding gamemode)
			solved(box, order);
			cout << endl << endl;
			//Congratulates the user and outputs the moved it took them to solve the square
			cout << "Congratulations! You completed the sqaure in " << count << " moves!" << endl << endl;
			//Sets solved state to true so the program goes back to the menu
			checkMe = true;
			system("pause");
			//Clears screen after user press a key
			system("cls");
		}
	}
	//If the user is playing using the decending gamemode then it would use the following if statement to check if the square is complete
	else if (order == 2)
	{
		//Checks if the numbers are in order of 8,7,6,5,4,3,2,1,0 (complete square)
		if ((box[0][0] == 8) && (box[0][1] == 7) && (box[0][2] == 6) && (box[1][0] == 5) && (box[1][1] == 4) && (box[1][2] == 3) && (box[2][0] == 2) && (box[2][1] == 1) && (box[2][2] == 0))
		{
			//Shows the solved state box setup turns the square green (for corrsponding gamemode)
			solved(box, order);
			cout << endl << endl;
			//Congratulates the user and outputs the moved it took them to solve the square
			cout << "Congratulations! You completed the sqaure in " << count << " moves!" << endl << endl;
			//Sets solved state to true so the program goes back to the menu
			checkMe = true;
			system("pause");
			//Clears screen after user press a key
			system("cls");
		}
	}
}
void showSquare(int box[square][square], int order)
{
	//If statement to show order based on gamemode (ascending or decending)
	if (order == 1)
	{
		cout << setfill('-') << setw(120) << "-" << setfill(' ') << endl;
		SetConsoleTextAttribute(console, 11); 	//Sets color to light blue for puzzle header
		cout << "\t\t\t\t\t   Solve in Ascending Order" << endl;
		SetConsoleTextAttribute(console, 15);//Back to white
		cout << setfill('-') << setw(120) << "-" << setfill(' ') << endl;
	}
	else
	{
		cout << setfill('-') << setw(120) << "-" << setfill(' ') << endl;
		SetConsoleTextAttribute(console, 11); 	//Sets color to light blue for puzzle header
		cout << "\t\t\t\t\t   Solve in Descending Order" << endl;
		SetConsoleTextAttribute(console, 15); //Back to white
		cout << setfill('-') << setw(120) << "-" << setfill(' ') << endl;
	}
	//Sets color to red for puzzle to indacte unsolved state
	SetConsoleTextAttribute(console, 12);

	//Moves square down
	cout << endl << endl;

	//First loop used to for each columns
	for (int x = 0; x < 3; x++) 
	{
		//Moves the square to the right and creates border lines
		cout << "\t\t\t\t\t\t" << setfill('-') << setw(13) << "-" << setfill(' ') << endl;
		cout << "\t\t\t\t\t\t";

		//Second loop used to output the numbers in the rows
		for (int i = 0; i < 3; i++) 
		{
			cout << "|"; //Used to make a border
			//If the number is 0 it is replaced with a space
			if (box[x][i] == 0) 
			{
				cout << " " << " " << " ";
			}
			//If no the number is outputed normally
			else 
			{
				cout << " " << box[x][i] << " ";
			}
		}
		//Last peice of the border in each column and gooes to the next line
		cout << "|" << endl;
	}
	//Completes the lines for the border
	cout << "\t\t\t\t\t\t" << setfill('-') << setw(13) << "-" << setfill(' ') << endl;
	cout << endl << endl;
	//Sets color back to white
	SetConsoleTextAttribute(console, 15);
}
void checkZero(int box[square][square], int &x, int &y)
{
	//First loop for columns
	for (int i = 0; i < 3; i++)
	{
		//Second loop for rows
		for (int j = 0; j < 3; j++)
		{
			//If number in the location is 0 then the x will be set to the column and y to the row number
			if (box[i][j] == 0)
			{
				x = i;
				y = j;
			}
		}
	}
}

void left(int box[square][square], int x, int y)
{
	//Temp value for y so y can be used again to check/switch locations 
	int yTemp = 0;
	//yTemp is now set to y moved 1 to the left
	yTemp = y - 1;

	//If the move is invalid the change would not go through (under 0)
	if (yTemp < 0)
	{
		//cout << "Invalid Move! Please try again!" << endl;  disabled for convenience
		//system("pause");
	}
	//If the move is valid the 0 will switch spots with the number it is replacing
	else
	{
		box[x][y] = box[x][yTemp];
		box[x][yTemp] = 0; 
	} 
}
void right(int box[square][square], int x, int y)
{
	//Temp value for y so y can be used again to check/switch locations 
	int yTemp = 0;
	//yTemp is now set to y moved 1 to the right
	yTemp = y + 1;

	//If the move is invalid the change would not go through (over 2)
	if (yTemp > 2)
	{
		//cout << "Invalid Move! Please try again!" << endl;disabled for convenience
		//system("pause");
	}
	else
	//If the move is valid the 0 will switch spots with the number it is replacing
	{
		box[x][y] = box[x][yTemp];
		box[x][yTemp] = 0;
	}
}
void up(int box[square][square], int x, int y)
{
	//Temp value for x so x can be used again to check/switch locations 
	int xTemp = 0;
	//xTemp is now set to x moved 1 up
	xTemp = x - 1;

	//If the move is invalid the change would not go through (under 0)
	if (xTemp < 0)
	{
		//cout << "Invalid Move! Please try again!" << endl;  disabled for convenience
		//system("pause");
	}
	//If the move is valid the 0 will switch spots with the number it is replacing
	else
	{
		box[x][y] = box[xTemp][y];
		box[xTemp][y] = 0;
	}
}
void down(int box[square][square], int x, int y)
{
	//Temp value for x so x can be used again to check/switch locations 
	int xTemp = 0;
	//xTemp is now set to x moved 1 down
	xTemp = x + 1;

	//If the move is invalid the change would not go through (over 2)
	if (xTemp > 2)
	{
		//cout << "Invalid Move! Please try again!" << endl; disabled for convenience 
		//system("pause"); 
	}
	//If the move is valid the 0 will switch spots with the number it is replacing
	else
	{
		box[x][y] = box[xTemp][y];
		box[xTemp][y] = 0;
	}
}