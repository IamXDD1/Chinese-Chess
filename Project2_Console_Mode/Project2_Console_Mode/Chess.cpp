#include "Chess.h"
#include "GameManager.h"

// Chess
bool Chess::kingKing(vector<Pos>& cango) 
{
	if (chess_type % 10 == 7)
	{
		for (int i = 0; i < cango.size(); i++)
		{
			if (cango[i].x < 8)
			{
				for (int j = cango[i].x; j < 9; j++)
				{
					if (Board::getChess(j, cango[i].y).chess_type % 10 != -1)
					{
						if (Board::getChess(j, cango[i].y).chess_type % 10 == 7)
						{
							cango.erase(cango.begin() + i);
							return true;
						}
						break;
					}
				}
			}
			if (cango[i].x > 0)
			{
				for (int j = cango[i].x; j >= 0; j--)
				{
					if (Board::getChess(j, cango[i].y).chess_type != -1)
					{
						if (Board::getChess(j, cango[i].y).chess_type % 10 == 7)
						{
							cango.erase(cango.begin() + i);
							return true;
						}
						break;
					}
				}
			}
			if (cango[i].y < 9)
			{
				for (int j = cango[i].y; j < 10; j++)
				{
					if (Board::getChess(cango[i].x, j).chess_type != -1)
					{
						if (Board::getChess(cango[i].x, j).chess_type % 10 == 7)
						{
							cango.erase(cango.begin() + i);
							return true;
						}
						break;
					}
				}
			}
			if (cango[i].y > 0)
			{
				for (int j = cango[i].y; j >= 0; j--)
				{
					if (Board::getChess(cango[i].x, j).chess_type != -1)
					{
						if (Board::getChess(cango[i].x, j).chess_type % 10 == 7)
						{
							cango.erase(cango.begin() + i);
							return true;
						}
						break;
					}
				}
			}
		}
		return false;
	}
	else if(chess_type % 10 != -1)
	{
		int toBreak = 0;
		if (pos.x < 8)
		{
			for (int j = pos.x; j < 9; j++)
			{
				if (Board::getChess(j, pos.y).chess_type != -1)
				{
					if (Board::getChess(j, pos.y).chess_type % 10 == 7) toBreak++;
					return;
				}
			}
		}
		if (pos.x > 0)
		{
			for (int j = pos.x; j >= 0; j--)
			{
				if (Board::getChess(j, pos.y).chess_type != -1)
				{
					if (Board::getChess(j, pos.y).chess_type % 10 == 7) toBreak++;
					return;
				}
			}
			if (toBreak == 2)
			{
				cango.clear();
				return;
			}
		}
		if (pos.y < 9)
		{
			for (int j = pos.y; j < 10; j++)
			{
				if (Board::getChess(pos.x, j).chess_type != -1)
				{
					if (Board::getChess(pos.x, j).chess_type % 10 == 7) toBreak++;
					return;
				}
			}
			if (toBreak == 2)
			{
				cango.clear();
				return;
			}
		}
		if (pos.y > 0)
		{
			for (int j = pos.y; j >= 0; j--)
			{
				if (Board::getChess(pos.x, j).chess_type != -1)
				{
					if (Board::getChess(pos.x, j).chess_type % 10 == 7) toBreak++;
					return;
				}
			}
			if (toBreak == 2)
			{
				cango.clear();
				return;
			}
		}
		
	}
}

bool Chess::checkmate(int x, int y, vector<Pos>& cango)
{
		int type;
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
		else if(color == BLACK)
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
vector<Pos> General::moveable(int x, int y, vector<Pos>& cango)
{
	if (color == RED) // RED
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
	else if(color == BLACK)             // BLACK
	{
		if (x == 3) {
			cango.push_back({ y,x + 1 }); // y == 1 2 0
			if (y != 9) cango.push_back({ x, y - 1 }); // y == 1 2
			if (y != 7) cango.push_back({ x, y + 1 }); // y == 1 0
		}
		else if (x == 4)
		{
			cango.push_back({ x - 1, y }); // y == 1 2 0
			cango.push_back({ x + 1, y }); // y == 1 2 0
			if (y != 9) cango.push_back({ x, y - 1 }); // y == 1 2
			if (y != 7) cango.push_back({ x, y + 1 }); // y == 1 0
		}
		else if (x == 5)
		{
			cango.push_back({ x - 1, y }); // y == 1 2 0
			if (y != 9) cango.push_back({ x, y - 1 }); // y == 1 2
			if (y != 7) cango.push_back({ x, y + 1 }); // y == 1 0
		}
	}
	checkCompanion(cango);
	kingKing(cango);
	return cango;
}

// Advisor
vector<Pos> Advisor::moveable(int x, int y, vector<Pos>& cango)
{
	if (!kingKing(cango))
	{
		if (color == RED)   // RED	
		{
			if (x != 4) cango.push_back({ 1, 4 });
			else
			{
				cango.push_back({ x + 1, y - 1 });
				cango.push_back({ x - 1, y - 1 });
				cango.push_back({ x + 1, y + 1 });
				cango.push_back({ x - 1, y + 1 });
			}
		}
		else if(color == BLACK)             // BLACK
		{
			if (x != 4) cango.push_back({ 8, 4 });
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
	return cango;
}

// Elephant
vector<Pos> Elephant::moveable(int x, int y, vector<Pos>& cango)
{
	if (!kingKing(cango))
	{
		if (x > 1 && y > 1)
		{
			if (Board::getChess(x - 1, y - 1).chess_type == -1) cango.push_back({ x - 2, y - 2 });
		}
		if (x < 6 && y < 7)
		{
			if (Board::getChess(x + 1, y + 1).chess_type == -1) cango.push_back({ x + 2 , y + 2 });
		}
		if (x > 1 && y < 7)
		{
			if (Board::getChess(x - 1, y + 1).chess_type == -1) cango.push_back({ x - 2,  y + 2 });
		}
		if (x < 6 && y > 1)
		{
			if (Board::getChess(x + 1, y - 1).chess_type == -1) cango.push_back({ x + 2,  y - 2 });
		}
		checkCompanion(cango);
	}
	return cango;
}

// Chariot
vector<Pos> Chariot::moveable(int x, int y, vector<Pos>& cango)
{
	if (!kingKing(cango))
	{
		if (y != 8)
		{
			for (int i = y + 1; i < 9; i++)
			{
				cango.push_back({ x, i });
				int chessType = Board::getChess(x, i).chess_type;
				if (chessType != -1)
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
				if (chessType != -1)
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
				if (chessType != -1)
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
				if (chessType != -1)                                  // chesstype = -1 ?
				{
					break;
				}
			}
		}
		checkCompanion(cango);
	}
	return cango;
}

// Horse
vector<Pos> Horse::moveable(int x, int y, vector<Pos>& cango)
{
	if (!kingKing(cango))
	{
		if (y < 8)
		{
			if (Board::getChess(x, y + 1).chess_type == -1)
			{
				if (x < 8) cango.push_back({ x + 1, y + 2 }); // 下下右
				if (x > 0) cango.push_back({ x - 1, y + 2 }); // 下下左
			}
		}
		if (y > 1)
		{
			if (Board::getChess(y - 1, x).chess_type == -1)
			{
				if (x < 8) cango.push_back({ x + 1, y - 2 }); // 上上右
				if (x > 0) cango.push_back({ x - 1, y - 2 }); // 上上左
			}
		}
		if (x < 7)
		{
			if (Board::getChess(y, x + 1).chess_type == -1)
			{
				if (y > 0) cango.push_back({ x + 2, y + 1 }); // 右右上
				if (y < 9) cango.push_back({ x + 2, y - 1 }); // 右右左
			}
		}
		if (x > 1)
		{
			if (Board::getChess(y, x - 1).chess_type == -1)
			{
				if (y > 0) cango.push_back({ x - 2, y + 1 }); // 左左上
				if (y < 9) cango.push_back({ x - 2, y - 1 }); // 左左下
			}
		}
		checkCompanion(cango);
	}
	return cango;
}

// Cannon
vector<Pos> Cannon::moveable(int x, int y, vector<Pos>& cango)
{
	if (!kingKing(cango))
	{
		vector<Pos> temp;
		if (y != 8)
		{
			for (int i = y + 1; i < 9; i++)
			{
				int chessType = Board::getChess(x, i).chess_type;
				if (chessType != -1)
				{
					for (int j = i + 1; j < 9; j++)
					{
						chessType = Board::getChess(x, j).chess_type;
						if (chessType != -1)
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
				if (chessType != -1)
				{
					for (int j = i - 1; j >= 0; j--)
					{
						chessType = Board::getChess(x, j).chess_type;
						if (chessType != -1)
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
				if (chessType != -1)
				{
					for (int j = i + 1; j < 9; j++)
					{
						chessType = Board::getChess(j, y).chess_type;
						if (chessType != -1)
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
				if (chessType != -1)
				{
					for (int j = i - 1; j >= 0; j--)
					{
						chessType = Board::getChess(j, y).chess_type;
						if (chessType != -1)
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
	return cango;
}

// Soldier
vector<Pos> Soldier::moveable(int x, int y, vector<Pos>& cango)
{
	if (!kingKing(cango))
	{
		if (color == 1)
		{
			if (y != 0) cango.push_back({ x, y - 1 });
			if (y < 5) // cross the river
			{
				if (x != 9) cango.push_back({ x + 1, y });
				if (x != 0) cango.push_back({ x - 1, y });
			}
		}
		else if (color == 2)
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
	return cango;
}