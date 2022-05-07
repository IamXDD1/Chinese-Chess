#include "Chess.h"

// Chess

vector<pair<int, int>> Chess::checkCompanion(int type, vector<pair<int, int>>& cango, Board board)
{
	for (int i = 0; i < cango.size(); i++)
	{
		if (type / 10 != 0)
		{
			if (board.getChess(cango[i].first, cango[i].second) / 10 != 0)
			{
				cango.erase(cango.begin() + i);
				i--;
			}
		}
		else
		{
			if (board.getChess(cango[i].first, cango[i].second) / 10 == 0)
			{
				cango.erase(cango.begin() + i);
				i--;
			}
		}
	}
	return cango;
}

// General
void General::moveable(int x, int y, int num, vector<pair<int, int>>& cango, Board board)
{
	if (num / 10 != 0) // RED
	{
		if (x == 3) {
			cango.push_back({ y,x + 1 }); // y == 1 2 0
			if (y != 0) cango.push_back({ y - 1 ,x }); // y == 1 2
			if (y != 2) cango.push_back({ y + 1,x }); // y == 1 0
		}
		else if (x == 4)
		{
			cango.push_back({ y,x - 1 }); // y == 1 2 0
			cango.push_back({ y,x + 1 }); // y == 1 2 0
			if (y != 0) cango.push_back({ y - 1,x }); // y == 1 2
			if (y != 2) cango.push_back({ y + 1,x }); // y == 1 0
		}
		else if (x == 5)
		{
			cango.push_back({ y,x - 1 }); // y == 1 2 0
			if (y != 0) cango.push_back({ y - 1 ,x }); // y == 1 2
			if (y != 2) cango.push_back({ y + 1,x }); // y == 1 0
		}
	}
	else               // BLACK
	{
		if (x == 3) {
			cango.push_back({ y,x + 1 }); // y == 1 2 0
			if (y != 9) cango.push_back({ y - 1 ,x }); // y == 1 2
			if (y != 7) cango.push_back({ y + 1,x }); // y == 1 0
		}
		else if (x == 4)
		{
			cango.push_back({ y,x - 1 }); // y == 1 2 0
			cango.push_back({ y,x + 1 }); // y == 1 2 0
			if (y != 9) cango.push_back({ y - 1,x }); // y == 1 2
			if (y != 7) cango.push_back({ y + 1,x }); // y == 1 0
		}
		else if (x == 5)
		{
			cango.push_back({ y,x - 1 }); // y == 1 2 0
			if (y != 9) cango.push_back({ y - 1 ,x }); // y == 1 2
			if (y != 7) cango.push_back({ y + 1,x }); // y == 1 0
		}
	}
	vector<pair<int, int>> temp;
	cango = checkCompanion(num, cango, board);
}

bool General::move(int x, int y)
{
	return false;
}

bool General::checkmate(int x, int y)
{
	return false;
}


// Advisor
void Advisor::moveable(int x, int y, int num, vector<pair<int, int>>& cango, Board board)
{
	if (num / 10 != 0)   // RED	
	{ 
		if (x != 4) cango.push_back({ 1, 4 });
		else
		{
			cango.push_back({ y - 1, x + 1 });
			cango.push_back({ y - 1, x - 1 });
			cango.push_back({ y + 1, x + 1 });
			cango.push_back({ y + 1, x - 1 });
		}	
	}
	else                 // BLACK
	{
		if (x != 4) cango.push_back({ 8, 4 });
		else
		{
			cango.push_back({ y - 1, x + 1 });
			cango.push_back({ y - 1, x - 1 });
			cango.push_back({ y + 1, x + 1 });
			cango.push_back({ y + 1, x - 1 });
		}
	}
	cango = checkCompanion(num, cango, board);
}

bool Advisor::move(int x, int y)
{
	return false;
}

bool Advisor::checkmate(int x, int y)
{
	return false;
}


// Elephant
void Elephant::moveable(int x, int y, int num, vector<pair<int, int>>& cango, Board board)
{
}

bool Elephant::move(int x, int y)
{
	return false;
}

bool Elephant::checkmate(int x, int y)
{
	return false;
}


// Chariot
void Chariot::moveable(int x, int y, int num, vector<pair<int, int>>& cango, Board board)
{
}

bool Chariot::move(int x, int y)
{
	return false;
}

bool Chariot::checkmate(int x, int y)
{
	return false;
}


// Horse
void Horse::moveable(int x, int y, int num, vector<pair<int, int>>& cango, Board board)
{
}

bool Horse::move(int x, int y)
{
	return false;
}

bool Horse::checkmate(int x, int y)
{
	return false;
}

// Cannon
void Cannon::moveable(int x, int y, int num, vector<pair<int, int>>& cango, Board board)
{
	bool object = false; // wheather the position have a piece
	
}
bool Cannon::move(int x, int y) {

	return true;
}
bool Cannon::checkmate(int x, int y) {
	return true;
}


// Soldier
void Soldier::moveable(int x, int y, int num, vector<pair<int, int>>& cango, Board board)
{
}

bool Soldier::move(int x, int y)
{
	return false;
}

bool Soldier::checkmate(int x, int y)
{
	return false;
}

bool Chess::move(int x, int y)
{
	return false;
}
