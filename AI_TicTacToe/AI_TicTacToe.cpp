// AI_TicTacToe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>

using namespace std;
//
//Global Declarations
char pos[3][3] = { ' ',' ',' ',' ',' ',' ',' ',' ', ' ' };
char c_symb;
char p_symb;
Displays gameDisplay;
Strategy gameStrategy;

//Methods declaration
void firstMove(bool);
bool moveAssign(int);

int main()
{
	//gameDisplay.menu(); Disabled for faster debugging
	gameDisplay.board(pos);

	c_symb = gameDisplay.getCSymb();
	p_symb = gameDisplay.getPSymb();
	bool compFirst = gameDisplay.isCompFirst();
	gameStrategy = Strategy(c_symb, p_symb);

	firstMove(compFirst);

	int currentTurn;
	for (currentTurn = 2; currentTurn < 6; currentTurn++)
	{
		gameStrategy.computerMove(pos, currentTurn);
		Sleep(500);
		gameDisplay.board(pos);
		gameStrategy.checkForWin(pos);

		int move;
		cout << "Enter Position: ";
		cin >> move;
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
		} while (!symbolAssigned);
		gameDisplay.board(pos);
		gameStrategy.checkForWin(pos);
	}

	gameDisplay.gameDraw();
	_getch();
    return 0;
}

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



