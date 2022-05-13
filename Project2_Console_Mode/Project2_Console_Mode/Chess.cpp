#include "Chess.h"
#include "GameManager.h"

// Chess
void Chess::kingKing(vector<Pos>& cango)
{
	for (int i = 0; i < cango.size(); i++)
	{
		return;
	}
}

bool Chess::move(int x, int y)
{
	return false;
	//File file; // just for test
	//board.moveChess(file, color, character, x1, y1, x2, y2);
}

bool Chess::checkmate(int x, int y)
{
	int type;
	vector<Pos> cango = moveable(x, y, cango);
	for (int i = 0; i < cango.size(); i++)
	{
		type = Board::getChess(cango[i].x, cango[i].y).chess_type;
		if (type / 10 != chess_type && type % 10 == 7) return true;
	}
	return false;
}

void Chess::checkCompanion(vector<Pos>& cango)
{
	for (int i = 0; i < cango.size(); i++)
	{
		if (color == RED)
		{
			if (Board::getChess(cango[i].x, cango[i].y).color == RED)
			{
				cango.erase(cango.begin() + i);
				i--;
			}
		}
		else if (color == BLACK)
		{
			if (Board::getChess(cango[i].x, cango[i].y).color == BLACK)
			{
				cango.erase(cango.begin() + i);
				i--;
 			}
		}
	}
	return;
}

// General
void General::moveable(int x, int y, vector<Pos>& cango)
{
	if (color == BLACK) // RED
	{
		if (x == 3) {
			cango.push_back({ x + 1, y }); // y == 1 2 0
			if (y != 0) cango.push_back({ x,y - 1 }); // y == 1 2
			if (y != 2) cango.push_back({ x, y + 1 }); // y == 1 0
		}
		else if (x == 4)
		{
			cango.push_back({ x - 1, y }); // y == 1 2 0
			cango.push_back({ x + 1, y }); // y == 1 2 0
			if (y != 0) cango.push_back({ x, y - 1 }); // y == 1 2
			if (y != 2) cango.push_back({ x, y + 1 }); // y == 1 0
		}
		else if (x == 5)
		{
			cango.push_back({ y,x - 1 }); // y == 1 2 0
			if (y != 0) cango.push_back({ x, y - 1 }); // y == 1 2
			if (y != 2) cango.push_back({ x, y + 1 }); // y == 1 0
		}
	}
	else if (color == RED)        // BLACK
	{
		if (x == 3) {
			cango.push_back({ y,x + 1 }); // y == 1 2 0
			if (y != 9) cango.push_back({ x, y + 1 }); // y == 1 2
			if (y != 7) cango.push_back({ x, y - 1 }); // y == 1 0
		}
		else if (x == 4)
		{
			cango.push_back({ x - 1, y }); // y == 1 2 0
			cango.push_back({ x + 1, y }); // y == 1 2 0
			if (y != 9) cango.push_back({ x, y + 1 }); // y == 1 2
			if (y != 7) cango.push_back({ x, y - 1 }); // y == 1 0
		}
		else if (x == 5)
		{
			cango.push_back({ x - 1, y }); // y == 1 2 0
			if (y != 9) cango.push_back({ x, y + 1 }); // y == 1 2
			if (y != 7) cango.push_back({ x, y - 1 }); // y == 1 0
		}
	}
	checkCompanion(cango);
}


// Advisor
void Advisor::moveable(int x, int y, vector<Pos>& cango)
{
	if (color == BLACK)   // RED	
	{
		if (x != 4) cango.push_back({ 4, 1 });
		else
		{
			cango.push_back({ x + 1, y - 1 });
			cango.push_back({ x - 1, y - 1 });
			cango.push_back({ x + 1, y + 1 });
			cango.push_back({ x - 1, y + 1 });
		}
	}
	else if (color == RED)          // BLACK
	{
		if (x != 4) cango.push_back({ 4, 8 });
		else
		{
			cango.push_back({ x + 1, y - 1 });
			cango.push_back({ x - 1, y - 1 });
			cango.push_back({ x + 1, y + 1 });
			cango.push_back({ x - 1, y + 1 });
		}
	}
	checkCompanion(cango);
}


// Elephant
void Elephant::moveable(int x, int y, vector<Pos>& cango)
{
	if (x > 1 && y > 1)
	{
		if (Board::getChess(x - 1, y - 1).chess_type == NULL_CHESS) cango.push_back({ x - 2, y - 2 });
	}
	if (x < 6 && y < 7)
	{
		if (Board::getChess(x + 1, y + 1).chess_type == NULL_CHESS) cango.push_back({ x + 2 , y + 2 });
	}
	if (x > 1 && y < 7)
	{
		if (Board::getChess(x - 1, y + 1).chess_type == NULL_CHESS) cango.push_back({x - 2,  y + 2 });
	}
	if (x < 6 && y > 1)
	{
		if (Board::getChess(x + 1, y - 1).chess_type == NULL_CHESS) cango.push_back({x + 2,  y - 2 });
	}
	checkCompanion(cango);
}


// Chariot
void Chariot::moveable(int x, int y, vector<Pos>& cango)
{
	if (y != 8)
	{
		for (int i = y + 1; i < 9; i++)
		{
			cango.push_back({ x, i });
			int chessType = Board::getChess(x, i).chess_type;
			if (chessType != NULL_CHESS)
			{
				break;
			}
		}
	}
	if (y != 0)
	{
		for (int i = y - 1; i >= 0; i--)
		{
			cango.push_back({ x, i });
			int chessType = Board::getChess(x, i).chess_type;
			if (chessType != NULL_CHESS)
			{
				break;
			}
		}
	}
	if (x != 9)
	{
		for (int i = x + 1; i < 9; i++)
		{
			cango.push_back({ i, y });
			int chessType = Board::getChess(i, y).chess_type;
			if (chessType != NULL_CHESS)
			{
				break;
			}
		}
	}
	if (x != 0)
	{
		for (int i = x - 1; i >= 0; i--)
		{
			cango.push_back({ i, y });
			int chessType = Board::getChess(i, y).chess_type;
			if (chessType != NULL_CHESS)
			{
				break;
			}
		}
	}
	checkCompanion(cango);
}


// Horse
void Horse::moveable(int x, int y, vector<Pos>& cango)
{
	if (y < 8)
	{
		if (Board::getChess(x, y + 1).chess_type == NULL_CHESS)
		{
			if (x < 8) cango.push_back({ x + 1, y + 2 }); // 下下右
			if (x > 0) cango.push_back({ x - 1, y + 2 }); // 下下左
		}
	}
	if (y > 1)
	{
		if (Board::getChess(y - 1, x).chess_type == NULL_CHESS)
		{
			if (x < 8) cango.push_back({ x + 1, y - 2 }); // 上上右
			if (x > 0) cango.push_back({ x - 1, y - 2 }); // 上上左
		}
	}
	if (x < 7)
	{
		if (Board::getChess(y, x + 1).chess_type == NULL_CHESS)
		{
			if (y > 0) cango.push_back({ x + 2, y + 1 }); // 右右上
			if (y < 9) cango.push_back({ x + 2, y - 1 }); // 右右左
		}
	}
	if (x > 1)
	{
		if (Board::getChess(y, x - 1).chess_type == NULL_CHESS)
		{
			if (y > 0) cango.push_back({ x - 2, y + 1 }); // 左左上
			if (y < 9) cango.push_back({ x - 2, y - 1 }); // 左左下
		}
	}
	checkCompanion(cango);
}

// Cannon
void Cannon::moveable(int x, int y, vector<Pos>& cango)
{
	vector<Pos> temp;
	if (y != 8)
	{
		for (int i = y + 1; i < 9; i++)
		{
			int chessType = Board::getChess(x, i).chess_type;
			if (chessType != NULL_CHESS)
			{
				for (int j = i + 1; j < 9; j++)
				{
					chessType = Board::getChess(x, j).chess_type;
					if (chessType != NULL_CHESS)
					{
						cango.push_back({ x, j });
						break;
					}
				} 
				break;
			}
			cango.push_back({ x, i });
		}
	}
	if (y != 0)
	{
		for (int i = y - 1; i >= 0; i--)
		{
			int chessType = Board::getChess(x, i).chess_type;
			if (chessType != NULL_CHESS)
			{
				for (int j = i - 1; j >= 0; j--)
				{
					chessType = Board::getChess(x, j).chess_type;
					if (chessType != NULL_CHESS)
					{
						cango.push_back({ x, j });
						break;
					}
				}
				break;
			}
			cango.push_back({ x, i });
		}
	}
	if (x != 9)
	{
		for (int i = x + 1; i < 9; i++)
		{
			int chessType = Board::getChess(i, y).chess_type;
			if (chessType != NULL_CHESS)
			{
				for (int j = i + 1; j < 9; j++)
				{
					chessType = Board::getChess(j, y).chess_type;
					if (chessType != NULL_CHESS)
					{
						cango.push_back({ j, y });
						break;
					}
				}
				break;
			}
			cango.push_back({ i, y });
		}
	}
	if (x != 0)
	{
		for (int i = x - 1; i >= 0; i--)
		{
			int chessType = Board::getChess(i, y).chess_type;
			if (chessType != NULL_CHESS)
			{
				for (int j = i - 1; j >= 0; j--)
				{
					chessType = Board::getChess(j, y).chess_type;
					if (chessType != NULL_CHESS)
					{
						cango.push_back({ j, y });
						break;
					}
				}
				break;
			}
			cango.push_back({ i, y });
		}
	}
	checkCompanion(cango);
}


// Soldier
void Soldier::moveable(int x, int y, vector<Pos>& cango)
{
	if (color == RED)
	{
		if (y != 0) cango.push_back({ x, y - 1 });
		if (y < 5) // cross the river
		{
			if (x != 9) cango.push_back({ x + 1, y });
			if (x != 0) cango.push_back({ x - 1, y });
		}
	}
	else if (color == BLACK)
	{
		if (y != 8) cango.push_back({ x, y + 1 });
		if (y > 4)// cross the river
		{
			if (x != 9) cango.push_back({ x + 1, y });
			if (x != 0) cango.push_back({ x - 1, y });
		}
	}
	checkCompanion(cango);
}
