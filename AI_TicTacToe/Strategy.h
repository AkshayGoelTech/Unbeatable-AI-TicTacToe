#pragma once

#include <iostream>
/*Class made by Akshay Goel (akshaygoel1@gmail.com).
This class contains methods for the different strategies which the computer
employs to beat the human player. This is the core AI code of the program*/
class Strategy
{
	char c_symb;
	char p_symb;
	Displays gameDisplay;
public:
	Strategy();
	Strategy(char, char);
	void computerMove(char[][3], int);
	void checkForWin(char[][3]);
	void putOnCorners(char[][3]);
	bool winMove(char[][3]);
	bool winBlock(char[][3]);
	bool blockFork2(char[][3]);
	bool makeFork1(char[][3]);
	bool blockFork1(char[][3], int);
	bool strategyAlpha(char[][3]);
	bool strategyBeta(char[][3], int);
	bool strategyGamma(char[][3]);
	void makeBestMove(char[][3]);
	~Strategy();
};

