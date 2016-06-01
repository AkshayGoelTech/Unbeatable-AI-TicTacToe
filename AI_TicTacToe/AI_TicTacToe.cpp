/* AI_TicTacToe.cpp : Defines the entry point for the console application.
Program created by Akshay Goel (akshaygoel1@gmail.com).
Note: sleep(int) has been included in several places solely to make it look like the computer is thinking.
*/

#include "stdafx.h"
#include <iostream>
#include <Windows.h>

using namespace std;


//Global Declarations
char pos[3][3] = { ' ',' ',' ',' ',' ',' ',' ',' ', ' ' };
char c_symb; //character symbol
char p_symb; //player symbol
Displays gameDisplay;
Strategy gameStrategy;

//Methods declaration
void firstMove(bool);
bool moveAssign(int);

int main()
{
	//Displaying the intro screen, choice menu, and game board
	gameDisplay.menu();
	gameDisplay.board(pos);

	c_symb = gameDisplay.getCSymb();
	p_symb = gameDisplay.getPSymb();
	bool compFirst = gameDisplay.isCompFirst();
	gameStrategy = Strategy(c_symb, p_symb);

	//Play the first move of the game followed by tuhe player if computer was first
	firstMove(compFirst); 
	if (compFirst)
	{
		int move;
		cout << "Enter Position: ";
		cin >> move;
		moveAssign(move);
		gameDisplay.board(pos);
	}

	//The game now begins
	int currentTurn = 2;
	for (currentTurn = 2; currentTurn < 6; currentTurn++)
	{
		gameStrategy.computerMove(pos, currentTurn);
		Sleep(500);
		gameDisplay.board(pos);
		gameStrategy.checkForWin(pos);

		if ((compFirst) && (currentTurn == 5)) {
			gameDisplay.gameDraw();
		}

		//Human can play his move
		int move;
		cout << "Enter Position: ";
		cin >> move;

		/*Loop in place to make sure the human player plays a legal move.
		A legal move can only be played on en empty, unoccupied spot
		*/
		bool symbolAssigned = false;
		do
		{
			symbolAssigned = moveAssign(move);
			if (!symbolAssigned)
			{
				gameDisplay.board(pos);
				cout << "\nYou Cannot Put There!...Enter Again -> ";
				cin >> move;
			}
			cout << "DEBUG: Assigning Symbol";
		} while (!symbolAssigned);

		//Displaying the game board and then checking if the computer or player won
		gameDisplay.board(pos);
		gameStrategy.checkForWin(pos);
		
	}
	
	/*If nobody wins, the program reaches this part and called gameDraw() 
	which declares a draw and ends game*/
	gameDisplay.gameDraw();
	_getch();
    return 0;
}

/*Method to play the first move.
@param compFirst true if the computer is first.
*/
void firstMove(bool compFirst)
{
	int move;
	cout << "\n";
	if (!compFirst)
	{
		cout << "Make your First Move..\n";
		cout << "Enter Position where you wish to enter: ";
		cin >> move;
		bool symbolAssigned = moveAssign(move);
	}
	else
	{
		cout << "Alright, I will Start..Lets See";
		pos[1][1] = c_symb;
		Sleep(500);
		gameDisplay.board(pos);
	}
}

/*Method used to assign the player's symbol to a position on
the board
@param posOnBoard The position where the player has asked to place his symbol
@return returns true if symbol was succesfully placed. False if the position was already taken
*/
bool moveAssign(int posOnBoard)
{
	switch (posOnBoard)
	{
	case 1: if (pos[0][0] != ' ')
		return(false);
		pos[0][0] = p_symb;
		break;
	case 2: if (pos[0][1] != ' ')
		return(false);
		pos[0][1] = p_symb;
		break;
	case 3: if (pos[0][2] != ' ')
		return(false);
		pos[0][2] = p_symb;
		break;
	case 4: if (pos[1][0] != ' ')
		return(false);
		pos[1][0] = p_symb;
		break;
	case 5: if (pos[1][1] != ' ')
		return(false);
		pos[1][1] = p_symb;
		break;
	case 6: if (pos[1][2] != ' ')
		return(false);
		pos[1][2] = p_symb;
		break;
	case 7: if (pos[2][0] != ' ')
		return(false);
		pos[2][0] = p_symb;
		break;
	case 8: if (pos[2][1] != ' ')
		return(false);
		pos[2][1] = p_symb;
		break;
	case 9: if (pos[2][2] != ' ')
		return(false);
		pos[2][2] = p_symb;
		break;
	default: return false;
	}

	gameDisplay.board(pos);
	return(true);
}



