#include "stdafx.h"
#include "Strategy.h"
//#include <iostream>
#include <random>
#include <time.h>

using namespace std;

Strategy::Strategy() {

}

Strategy::Strategy(char comp, char player)
{
	c_symb = comp;
	p_symb = player;
}

/*This is the method called by our main funcion everytime the computer
has to make its move. Each innrer method has been placed based on priority.
The methods called first have a higher prioirty than the ones below. On performing
the method, if the computer has NOT played a move, then the method has failed.
Hence moveDone will get a false value*/
void Strategy::computerMove(char pos[][3], int turn)
{
	if (pos[1][1] == ' ')
	{
		pos[1][1] = c_symb;
		return;
	}

	if (pos[1][1] == p_symb && turn == 2) {
		putOnCorners(pos);
		return;
	}

	bool moveDone = false;

	moveDone = winMove(pos);
	if (moveDone)
	{
		return;
	}

	moveDone = winBlock(pos);
	if (moveDone)
	{
		return;
	}

	moveDone = blockFork2(pos);
	if (moveDone)
	{
		return;
	}

	moveDone = makeFork1(pos);
	if (moveDone)
	{
		return;
	}

	moveDone = blockFork1(pos, turn);
	if (moveDone) {
		return;
	}

	moveDone = strategyAlpha(pos);
	if (moveDone) {
		return;
	}

	moveDone = strategyBeta(pos, turn);
	if (moveDone) {
		return;
	}

	moveDone = strategyGamma(pos);
	if (moveDone) {
		return;
	}

	makeBestMove(pos);
}

void Strategy::checkForWin(char pos[][3]) {

	float rowSum, colSum, diagonal1Sum, diagonal2Sum = 0;

	//Checking if a win has been made in a row or a coloumn
	for (int i = 0; i < 3; i++) {
		rowSum = 0;
		colSum = 0;
		for (int j = 0; j < 3; j++) {
			if (pos[i][j] != ' ')
				rowSum = rowSum + pos[i][j];
			if (pos[j][i] != ' ')
				colSum = colSum + pos[j][i];
		}
		if (((float)(rowSum / c_symb) == 3.0) || ((float)(colSum / c_symb) == 3.0))
			gameDisplay.computerWins();
		
		if (((float)(rowSum / p_symb) == 3.0) || ((float)(colSum / p_symb) == 3.0))
			gameDisplay.playerWins();
		
	}

	//Checking if a win has been made in one of the two diagonals
	diagonal1Sum = pos[0][0] + pos[1][1] + pos[2][2];
	diagonal2Sum = pos[2][0] + pos[1][1] + pos[0][2];

	if (((float)(diagonal1Sum / c_symb) == 3.0) || ((float)(diagonal2Sum / c_symb) == 3.0))
		gameDisplay.computerWins();	

	if (((float)(diagonal1Sum / p_symb) == 3.0) || ((float)(diagonal2Sum / p_symb) == 3.0))
		gameDisplay.playerWins();
}

void Strategy::putOnCorners(char pos[][3])
{
	time_t t;
	srand(time(&t));
	int rnum = rand() % 4;

	switch (rnum)
	{
	case 0:pos[0][0] = c_symb;
		break;

	case 1:pos[0][2] = c_symb;
		break;

	case 2:pos[2][0] = c_symb;
		break;

	case 3:pos[2][2] = c_symb;
		break;
	default: cout << "Random Number Error!";
		_getch();
		exit(0);
	}
}

bool Strategy::winMove(char pos[][3])
{
	//Checking if the computer has won in any row or coloumn
	for (int i = 0; i < 3; i++) {
		float rowSum = 0;
		float colSum = 0;
		int emptyRowPos = -1;
		int emptyColPos = -1;

		for (int j = 0; j < 3; j++)
		{
			if (pos[i][j] != ' ')
				rowSum = rowSum + pos[i][j];
			else
				emptyRowPos = j;

			if (pos[j][i] != ' ')
				colSum = colSum + pos[j][i];
			else
				emptyColPos = j;
		}
		if ((float)(rowSum / c_symb == 2.0)) {
			pos[i][emptyRowPos] = c_symb;
			return true;
		}
		if ((float)(colSum / c_symb == 2.0)) {
			pos[emptyColPos][i] = c_symb;
			return true;
		}
	}

	//Checking if the computer has won in the first diagonal at [0,0], [1,1], [2,2]
	float diagSum = 0;
	int emptyDiagPos = -1;	
	for (int i = 0; i < 3; i++)
	{
		if (pos[i][i] != ' ')
			diagSum = diagSum + pos[i][i];
		else
			emptyDiagPos = i;
	}
	if ((float)(diagSum / c_symb) == 2.0)
	{
		pos[emptyDiagPos][emptyDiagPos] = c_symb;
		return true;
	}

	//Checking if the computer has won in the other diagonal at [2,0], [1,1], [0,2]
	diagSum = 0;
	int emptyDiagPos_i = -1;
	int emptyDiagPos_j = -1;
	for (int i = 2, j = 0; j < 3; i--, j++)
	{
		if (pos[i][j] != ' ')
			diagSum = diagSum + pos[i][j];
		else
		{
			emptyDiagPos_i = i;
			emptyDiagPos_j = j;
		}			
	}

		if ((float)(diagSum / c_symb) == 2.0)
		{
			pos[emptyDiagPos_i][emptyDiagPos_j] = c_symb;
			return true;
		}

	return false;
}

bool Strategy::winBlock(char pos[][3])
{
	//Checking if the player has won in any row or coloumn and blocking it
	for (int i = 0; i < 3; i++) {
		float rowSum = 0;
		float colSum = 0;
		int emptyRowPos = -1;
		int emptyColPos = -1;

		for (int j = 0; j < 3; j++)
		{
			if (pos[i][j] != ' ')
				rowSum = rowSum + pos[i][j];
			else
				emptyRowPos = j;

			if (pos[j][i] != ' ')
				colSum = colSum + pos[j][i];
			else
				emptyColPos = j;
		}
		if ((float)(rowSum / p_symb == 2.0)) {
			pos[i][emptyRowPos] = c_symb;
			return true;
		}
		if ((float)(colSum / p_symb == 2.0)) {
			pos[emptyColPos][i] = c_symb;
			return true;
		}
	}

	//Checking if the player has won in the first diagonal at [0,0], [1,1], [2,2] and blocking it
	float diagSum = 0;
	int emptyDiagPos = -1;
	for (int i = 0; i < 3; i++)
	{
		if (pos[i][i] != ' ')
			diagSum = diagSum + pos[i][i];
		else
			emptyDiagPos = i;
	}
	if ((float)(diagSum / p_symb) == 2.0)
	{
		pos[emptyDiagPos][emptyDiagPos] = c_symb;
		return true;
	}

	//Checking if the player has won in the other diagonal at [2,0], [1,1], [0,2] and blocking it
	diagSum = 0;
	int emptyDiagPos_i = -1;
	int emptyDiagPos_j = -1;
	for (int i = 2, j = 0; j < 3; i--, j++)
	{
		if (pos[i][j] != ' ')
			diagSum = diagSum + pos[i][j];
		else
		{
			emptyDiagPos_i = i;
			emptyDiagPos_j = j;
		}
	}

	if ((float)(diagSum / p_symb) == 2.0)
	{
		pos[emptyDiagPos_i][emptyDiagPos_j] = c_symb;
		return true;
	}

	return false;
	//test
}

bool Strategy::blockFork2(char pos[][3])
{

	for (int i = 0; i<3; i++) {
		for (int j = 0; j<3; j++)
		{
			if ((pos[1][1] == c_symb) && ((i + j) % 2 != 0) && 
				(pos[i][j] == p_symb) && (pos[i][abs(j - 1)] == ' ') && 
				(pos[i][abs(j + 1)] == ' ') && (pos[abs(i - 1)][j + 1] == p_symb) && 
				(pos[abs(i - 2)][j + 1] == ' '))
			{
				pos[i][j + 1] = c_symb;
				return true;
			}
		}
	}

	return false;
}

bool Strategy::makeFork1(char pos[][3])
{
	for (int i = 0; i<3; i += 2)
	{
		for (int j = 0; j<3; j += 2)
		{
			if (pos[1][1] == c_symb && pos[i][j] == c_symb && 
				pos[i][abs(j - 1)] == p_symb && pos[abs(i - 1)][j] == ' ' && 
				pos[i][abs(j - 2)] == ' ' && pos[abs(i - 2)][j] == ' ')
			{
				pos[abs(i - 2)][j] = c_symb;
				return true;
			}
		}
	}

	for (int i = 0; i<3; i += 2)
	{
		for (int j = 0; j<3; j += 2)
		{
			if (pos[1][1] == c_symb && pos[i][j] == c_symb && 
				pos[abs(i - 1)][j] == p_symb && pos[i][abs(j - 1)] == ' ' && 
				pos[abs(i - 2)][j] == ' ' && pos[i][abs(j - 2)] == ' ')
			{
				pos[i][abs(j - 2)] = c_symb;
				return true;
			}
		}
	}

	return false;
}

bool Strategy::blockFork1(char pos[][3], int turn)
{
	time_t t; 
	srand(time(&t));
	int rnum = rand() % 4;

	for (int i = 0; i<3; i += 2)
	{
		for (int j = 0; j<3; j += 2)
		{
			if (turn == 3 && pos[1][1] == c_symb && 
				pos[i][j] == p_symb && pos[abs(i - 2)][abs(j - 2)] == p_symb)
			{
				switch (rnum)
				{
				case 0: pos[0][1] = c_symb;
					return true;
				case 1: pos[1][2] = c_symb;
					return true;
				case 2: pos[2][1] = c_symb;
					return true;
				case 3: pos[1][0] = c_symb;
					return true;
				}
			}
		}
	}

	return false;
}

bool Strategy::strategyAlpha(char pos[][3])
{
	if (pos[1][1] == c_symb)
	{
		if (pos[0][0] == p_symb && pos[2][2] == ' ')
		{
			pos[2][2] = c_symb; 
			return true;
		}
		if (pos[0][2] == p_symb && pos[2][0] == ' ')
		{
			pos[2][0] = c_symb;
			return true;
		}
		if (pos[2][0] == p_symb && pos[0][2] == ' ')
		{
			pos[0][2] = c_symb;
			return true;
		}
		if (pos[2][2] == p_symb && pos[0][0] == ' ')
		{
			pos[0][0] = c_symb;
			return true;
		}

	}

	return false;
}

bool Strategy::strategyBeta(char pos[][3], int turn)
{
	for (int i = 0; i<3; i += 2) {
		for (int j = 0; j<3; j += 2)
		{
			if (turn == 3 && pos[1][1] == p_symb && 
				pos[i][j] == p_symb && pos[abs(i - 2)][abs(j - 2)] == c_symb)
			{
				time_t t;
				srand(time(&t));
				int randomNum = rand() % 2;

				switch (randomNum)
				{
				case 0: if (pos[i][abs(j - 2)] != ' ')
					break;
						else
							pos[i][abs(j - 2)] = c_symb;
					return true;
				case 1: if (pos[abs(i - 2)][j] != ' ')
					break;
						else
							pos[abs(i - 2)][j] = c_symb;
					return true;
				}
			}
		}
	}
	return false;
}

bool Strategy::strategyGamma(char pos[][3])
{
	time_t t;
	srand(time(&t));
	int randomNum = rand() % 2;

	if (pos[1][1] == c_symb)
	{
		if (pos[0][1] == p_symb)
			switch (randomNum)
			{
			case 0: if (pos[2][0] != ' ')
				break;
					else
						pos[2][0] = c_symb;
				return true;
			case 1: if (pos[2][2] != ' ')
				break;
					else
						pos[2][2] = c_symb;
				return true;
			}

		if (pos[1][2] == p_symb)
			switch (randomNum)
			{
			case 0: if (pos[0][0] != ' ')
				break;
					else
						pos[0][0] = c_symb;
				return true;
			case 1: if (pos[2][0] != ' ')
				break;
					else
						pos[2][0] = c_symb;
				return true;
			}

		if (pos[2][1] == p_symb)
			switch (randomNum)
			{
			case 0: if (pos[0][0] != ' ')
				break;
					else
						pos[0][0] = c_symb;
				return true;
			case 1: if (pos[0][2] != ' ')
				break;
					else
						pos[0][2] = c_symb;
				return true;
			}

		if (pos[1][0] == p_symb)
			switch (randomNum)
			{
			case 0: if (pos[0][2] != ' ')
				break;
					else
						pos[0][2] = c_symb;
				return true;
			case 1: if (pos[2][2] != ' ')
				break;
					else
						pos[2][2] = c_symb;
				return true;
			}
	}
	return false;
}

void Strategy::makeBestMove(char pos[][3])
{
	while (true)
	{
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++)
			{
				if (pos[i][j] == ' ') {
					pos[i][j] = c_symb;
					return;
				}
			}
		}
	}
}
Strategy::~Strategy()
{
}
