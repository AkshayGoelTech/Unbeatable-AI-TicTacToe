#pragma once
class Displays
{
	char c_symb;
	char p_symb;
	bool c_first;
public:
	Displays();
	void board(char[][3]);
	void menu();
	void firstTime();
	char getCSymb();
	char getPSymb();
	bool isCompFirst();
	void computerWins();
	void playerWins();
	void gameDraw();
	~Displays();
};

