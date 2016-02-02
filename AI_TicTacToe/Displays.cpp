#include "stdafx.h"
#include "Displays.h"
#include <iostream>
#include <Windows.h>

using namespace std;

//Constructor
Displays::Displays()
{
	//Variables initialzied ONLY for faster debugging...remove these later
	c_symb = 'O';
	p_symb = 'X';
	c_first = false;
}

/*
Method to display the game board which the player and computer will play on.
@param pos This is the array that contains the index for each spot on the board
*/
void Displays::board(char pos[][3])
{
	//Just drawing the reference board
	system("cls");
	cout << "\t\t\t   TIC-TAC-TOE PROGRAM\n";
	int disp_num = 1;
	for (int i = 0; i<3; i++)
	{
		cout << "\t\t\t\t\t\t\t\t";
		for (int j = 0; j<3; j++)
		{
			cout << disp_num << " | ";
			disp_num++;
		}
		if (i == 2)
			break;
		else
			cout << "\n\t\t\t\t\t\t\t\t------------\n";
	}

	//Dynamic game board
	cout << "\n\n\n";
	cout << "\t     |     |     \n";
	cout << "\t  " << pos[0][0] << "  |  " << pos[0][1] << "  |  " << pos[0][2] << "   \n";
	cout << "\t_____|_____|_____\n";
	cout << "\t     |     |     \n";
	cout << "\t  " << pos[1][0] << "  |  " << pos[1][1] << "  |  " << pos[1][2] << "   \n";
	cout << "\t_____|_____|_____\n";
	cout << "\t     |     |     \n";
	cout << "\t  " << pos[2][0] << "  |  " << pos[2][1] << "  |  " << pos[2][2] << "   \n";
	cout << "\t     |     |     \n";

}

/*
Method where we will choose the symbol for the computer and human.
We will also decide if the computer goes first or not
*/
void Displays::menu()
{
	p_symb = 0;
	c_symb = 0;
	char p_first;
	c_first;

	system("cls");
	char option;
	cout << "\t\t\t   TIC-TAC-TOE PROGRAM\n";
	cout << "\t\t\t     By:Akshay Goel \n";

	cout << "\nIs this your First Time playing \nTic Tac Toe against the computer..? (y/n)\n";
	cin >> option;
	if (option == 'y' || option == 'Y')
	{
		cout << "Ok.\nPress any key to continue...";
		_getch();
		system("cls");
		firstTime();
	}

	system("cls");
	cout << "Before we begin,";
	cout << "\nWhat would you like to be? (X) or (O)\n\n";
	cin >> p_symb;		
	switch (p_symb)
	{
		case 'X':
		case 'x':p_symb = 'X';
			c_symb = 'O';
			break;
		case 'O':
		case 'o':
		case '0':p_symb = 'O';
			c_symb = 'X';
			break;
	}

	cout << "\nSo you will be " << p_symb;
	cout << "\nAnd I will play as " << c_symb;

	Sleep(500);
	cout << "\n\n\nNow tell me..Do you want to go first ? (y/n) ";
	cin >> p_first;
	switch (p_first)
	{
		case 'Y':c_first = false;
			break;
		case 'y':c_first = false;
			break;
		case 'N':c_first = true;
			break;
		case 'n':c_first = true;
			break;
	}
	cout << "\n";

	if (!c_first)
		cout << "Dont think you will win going first haha!";
	else
		cout << "Letting me go first? You just made my win easier haha!";
	Sleep(500);
	cout << "\n\nEnough talk, Lets Start..\t\t\t\tPress Any Key to Continue";
	_getch();

}

/*
Method runs the instructions if the game is being played the first time
*/

void Displays::firstTime()
{
	cout << "\t\t\t   TIC-TAC-TOE PROGRAM\n";
	cout << "\t\t\t     By:Akshay Goel \n"; 
	cout << "Hi"; Sleep(500);	cout << "\n\n I Am Computer"; Sleep(500);
	cout << "\nWelcome to Tic-Tac-Toe written by my creator Akshay Goel";
	Sleep(2);

	cout << "\nI'll run you quickly through the Instructions";
	Sleep(2);
	cout << "\n\n";
	cout << "\t\t\t\t\tPress any key to continue...\n";
	_getch();	
	system("cls");

	int disp_num = 1;

	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
		{
			cout << disp_num << " | ";
			disp_num++;
		}
		if (i == 2)
			break;
		else
			cout << "\n------------\n";
	}
	Sleep(2);
	cout << "\n\n What you see up there is a miniature version of the \nTic tac Toe Board we will play on.";
	Sleep(2);
	cout << "\n\nIm pretty Smart so I can place my symbol myself without any help"; 
	Sleep(1);
	cout << "\n\nBut you need to enter the number of the position you wish to\n enter your Symbol into";
	Sleep(2);	cout << "\n\nTHATS ALL!";
	cout << "\t\t\t\t\tPRESS ANY KEY TO CONTINUE\n";
	_getch();

}

/*Method which is called when the computer has won the game.
This method also terminates the program*/
void Displays::computerWins()
{
	//TODO
	cout << "CWIN";
	_getch();
	exit(0);
}

/*Method which is called when the player has won the game.
This method also terminates the program*/
void Displays::playerWins()
{
	cout << "PWIN";
	_getch();
	exit(0);
	//TODO
}

/*Method which is called when the game ends to be a draw*/
void Displays::gameDraw() 
{
	//TODO
	cout << "DRAW";
	_getch();
	exit(0);
}

//@return c_symb This contains the computers symbol
char Displays::getCSymb() {
	return c_symb;
}

//@return p_symb This contains the players symbol
char Displays::getPSymb() {
	return p_symb;
}

//@return c_first is true if the computer makes the first move
bool Displays::isCompFirst() {
	return c_first;
}

//Destructor
Displays::~Displays()
{
}
