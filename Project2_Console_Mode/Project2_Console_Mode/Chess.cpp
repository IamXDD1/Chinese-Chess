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
	if (x > 1 && y > 1)
	{
		cango.push_back({ y - 2,x - 2 });
	}
	if (x < 6 && y < 7)
	{
		cango.push_back({ y + 2,x + 2 });
	}
	if (x > 1 && y < 7)
	{
		cango.push_back({ y + 2,x - 2 });
	}
	if (x < 6 && y > 1)
	{
		cango.push_back({ y - 2,x + 2 });
	}
	cango = checkCompanion(num, cango, board);
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
	if (y != 8)
	{
		for (int i = y + 1; i < 9; i++)
		{
			cango.push_back({ i, x });
			int chessType = board.getChess(i, x);
			if (chessType != 0)
			{
				break;
			}
		}
	}
	if (y != 0)
	{
		for (int i = y - 1; i >= 0; i--)
		{
			cango.push_back({ i, x });
			int chessType = board.getChess(i, x);
			if (chessType != 0)
			{
				break;
			}
		}
	}
	if (x != 9)
	{
		for (int i = x + 1; i < 9; i++)
		{
			cango.push_back({ y, i });
			int chessType = board.getChess(y, i);
			if (chessType != 0)
			{
				break;
			}
		}
	}
	if (x != 0)
	{
		for (int i = x - 1; i >= 0; i--)
		{
			cango.push_back({ y, i });
			int chessType = board.getChess(y, i);
			if (chessType != 0)
			{
				break;
			}
		}
	}
	cango = checkCompanion(num, cango, board);
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
	if (y < 8)
	{
		if (board.getChess(y + 1, x) == 0)
		{
			if (x < 8) cango.push_back({ y + 2,x + 1 }); // 下下右
			if (x > 0) cango.push_back({ y + 2,x - 1 }); // 下下左
		}
	}
	if (y > 1)
	{
		if (board.getChess(y - 1, x) == 0)
		{
			if (x < 8) cango.push_back({ y - 2,x + 1 }); // 上上右
			if (x > 0) cango.push_back({ y - 2,x - 1 }); // 上上左
		}
	}
	if (x < 7)
	{
		if (board.getChess(y, x + 1) == 0)
		{
			if( y > 0) cango.push_back({ y + 1,x + 2 }); // 右右上
			if (y < 9) cango.push_back({ y - 1,x + 2 }); // 右右左
		}
	}
	if (x > 1)
	{
		if (board.getChess(y, x - 1) == 0)
		{
			if (y > 0) cango.push_back({ y + 1,x - 2 }); // 左左上
			if (y < 9) cango.push_back({ y - 1,x - 2 }); // 左左下
		}
	}
	cango = checkCompanion(num, cango, board);
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
	if (y != 8)
	{
		for (int i = y + 1; i < 9; i++)
		{
			cango.push_back({ i, x });
			int chessType = board.getChess(i, x);
			if (chessType != 0)
			{
				break;
			}
		}
	}
	if (y != 0)
	{
		for (int i = y - 1; i >= 0; i--)
		{
			cango.push_back({ i, x });
			int chessType = board.getChess(i, x);
			if (chessType != 0)
			{
				break;
			}
		}
	}
	if (x != 9)
	{
		for (int i = x + 1; i < 9; i++)
		{
			cango.push_back({ y, i });
			int chessType = board.getChess(y, i);
			if (chessType != 0)
			{
				break;
			}
		}
	}
	if (x != 0)
	{
		for (int i = x - 1; i >= 0; i--)
		{
			cango.push_back({ y, i });
			int chessType = board.getChess(y, i);
			if (chessType != 0)
			{
				break;
			}
		}
	}
	cango = checkCompanion(num, cango, board);
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
	if (y != 8) cango.push_back({ y + 1,x });
	if (y != 0) cango.push_back({ y - 1,x });
	if (x != 9) cango.push_back({ y,x + 1 });
	if (x != 0) cango.push_back({ y,x - 1 });
	cango = checkCompanion(num, cango, board);
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
