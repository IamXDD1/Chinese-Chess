#include "Chess.h"
#include "GameManager.h"

// Chess
bool Chess::kingKing(vector<Pos>& cango)
{
	// tested
	if (chess_type % 10 == 7) // general 
	{
		for (int i = 0; i < cango.size(); i++)
		{
			int toErase = 0;
			if (cango[i].x < 8)
			{
				for (int j = cango[i].x + 1; j < 9; j++)
				{
					if (Board::getChess(j, cango[i].y).chess_type != NULL_CHESS)
					{
						if (Board::getChess(j, cango[i].y).chess_type % 10 == 7)
						{
							toErase++;
							if (toErase == 2)
							{
								cango.erase(cango.begin() + i);
								return true;
							}
						}
						break;
					}
				}
			}
			if (cango[i].x > 0)
			{
				for (int j = cango[i].x - 1; j >= 0; j--)
				{
					if (Board::getChess(j, cango[i].y).chess_type != NULL_CHESS)
					{
						if (Board::getChess(j, cango[i].y).chess_type % 10 == 7)
						{
							toErase++;
							if (toErase == 2)
							{
								cango.erase(cango.begin() + i);
								return true;
							}
						}
						break;
					}
				}
			}
			if (cango[i].y < 9)
			{
				for (int j = cango[i].y + 1; j < 10; j++)
				{
					if (Board::getChess(cango[i].x, j).chess_type != NULL_CHESS)
					{
						if (Board::getChess(cango[i].x, j).chess_type % 10 == 7)
						{
							toErase++;
							if (toErase == 2)
							{
								cango.erase(cango.begin() + i);
								return true;
							}
						}
						break;
					}
				}
			}
			if (cango[i].y > 0)
			{
				for (int j = cango[i].y - 1; j >= 0; j--)
				{
					if (Board::getChess(cango[i].x, j).chess_type != NULL_CHESS)
					{
						if (Board::getChess(cango[i].x, j).chess_type % 10 == 7)
						{
							toErase++;
							if (toErase == 2)
							{
								cango.erase(cango.begin() + i);
								return true;
							}
						}
						break;
					}
				}
			}
		}
		return false;
	}
	else if (chess_type % 10 != NULL_CHESS) // pieces other than general
	{
		int toErase = 0;
		if (pos.x < 8) // go right
		{
			for (int j = pos.x; j < 9; j++)
			{
				if (Board::getChess(j, pos.y).chess_type != NULL_CHESS)
				{
					if (Board::getChess(j, pos.y).chess_type % 10 == 7)
					{
						toErase++;
						if (toErase == 2)
						{
							cango.clear();
							return true;
						}
					}
					break;
				}
			}
		}
		if (pos.x > 0) // go left
		{
			for (int j = pos.x; j >= 0; j--)
			{
				if (Board::getChess(j, pos.y).chess_type != NULL_CHESS)
				{
					if (Board::getChess(j, pos.y).chess_type % 10 == 7)
					{
						toErase++;
						if (toErase == 2)
						{
							cango.clear();
							return true;
						}
					}
					break;
				}
			}
		}
		if (pos.y < 9) // go down
		{
			for (int j = pos.y; j < 10; j++)
			{
				if (Board::getChess(pos.x, j).chess_type != NULL_CHESS)
				{
					if (Board::getChess(pos.x, j).chess_type % 10 == 7)
					{
						toErase++;
						if (toErase == 2)
						{
							cango.clear();
							return true;
						}
					}
					break;
				}
			}
		}
		if (pos.y > 0) // go up
		{
			for (int j = pos.y; j >= 0; j--)
			{
				if (Board::getChess(pos.x, j).chess_type != NULL_CHESS)
				{
					if (Board::getChess(pos.x, j).chess_type % 10 == 7)
					{
						toErase++;
						if (toErase == 2)
						{
							cango.clear();
							return true;
						}
					}
					break;
				}
			}
		}

		return false;
	}
}

bool Chess::board_kingKing(vector<Pos>& cango, Chess board[][9])
{

	// tested
	if (chess_type % 10 == 7) // general 
	{
		for (int i = 0; i < cango.size(); i++)
		{
			int toErase = 0;
			if (cango[i].x < 8)
			{
				for (int j = cango[i].x + 1; j < 9; j++)
				{
					if (board[cango[i].y][j].chess_type != NULL_CHESS)
					{
						if (board[cango[i].y][j].chess_type % 10 == 7)
						{
							toErase++;
							if (toErase == 2)
							{
								cango.erase(cango.begin() + i);
								return true;
							}
						}
						break;
					}
				}
			}
			if (cango[i].x > 0)
			{
				for (int j = cango[i].x - 1; j >= 0; j--)
				{
					if (board[cango[i].y][j].chess_type != NULL_CHESS)
					{
						if (board[cango[i].y][j].chess_type % 10 == 7)
						{
							toErase++;
							if (toErase == 2)
							{
								cango.erase(cango.begin() + i);
								return true;
							}
						}
						break;
					}
				}
			}
			if (cango[i].y < 9)
			{
				for (int j = cango[i].y + 1; j < 10; j++)
				{
					if (board[j][cango[i].x].chess_type != NULL_CHESS)
					{
						if (board[j][cango[i].x].chess_type % 10 == 7)
						{
							toErase++;
							if (toErase == 2)
							{
								cango.erase(cango.begin() + i);
								return true;
							}
						}
						break;
					}
				}
			}
			if (cango[i].y > 0)
			{
				for (int j = cango[i].y - 1; j >= 0; j--)
				{
					if (board[j][cango[i].x].chess_type != NULL_CHESS)
					{
						if (board[j][cango[i].x].chess_type % 10 == 7)
						{
							toErase++;
							if (toErase == 2)
							{
								cango.erase(cango.begin() + i);
								return true;
							}
						}
						break;
					}
				}
			}
		}
		return false;
	}
	else if (chess_type % 10 != NULL_CHESS) // pieces other than general
	{
		int toErase = 0;
		if (pos.x < 8) // go right
		{
			for (int j = pos.x; j < 9; j++)
			{
				if (board[pos.y][j].chess_type != NULL_CHESS)
				{
					if (board[pos.y][j].chess_type % 10 == 7)
					{
						toErase++;
						if (toErase == 2)
						{
							cango.clear();
							return true;
						}
					}
					break;
				}
			}
		}
		if (pos.x > 0) // go left
		{
			for (int j = pos.x; j >= 0; j--)
			{
				if (board[pos.y][j].chess_type != NULL_CHESS)
				{
					if (board[pos.y][j].chess_type % 10 == 7)
					{
						toErase++;
						if (toErase == 2)
						{
							cango.clear();
							return true;
						}
					}
					break;
				}
			}
		}
		if (pos.y < 9) // go down
		{
			for (int j = pos.y; j < 10; j++)
			{
				if (board[j][pos.x].chess_type != NULL_CHESS)
				{
					if (board[j][pos.x].chess_type % 10 == 7)
					{
						toErase++;
						if (toErase == 2)
						{
							cango.clear();
							return true;
						}
					}
					break;
				}
			}
		}
		if (pos.y > 0) // go up
		{
			for (int j = pos.y; j >= 0; j--)
			{
				if (board[j][pos.x].chess_type != NULL_CHESS)
				{
					if (board[j][pos.x].chess_type % 10 == 7)
					{
						toErase++;
						if (toErase == 2)
						{
							cango.clear();
							return true;
						}
					}
					break;
				}
			}
		}

		return false;
	}
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
}

void Chess::board_checkCompanion(vector<Pos>& cango, Chess board[][9])
{
	for (int i = 0; i < cango.size(); i++)
	{
		if (color == RED)
		{
			if (board[cango[i].y][cango[i].x].color == RED)
			{
				cango.erase(cango.begin() + i);
				i--;
			}
		}
		else if (color == BLACK)
		{
			if (board[cango[i].y][cango[i].x].color == BLACK)
			{
				cango.erase(cango.begin() + i);
				i--;
			}
		}
	}
}

// General
void General::moveable(int x, int y, vector<Pos>& cango) // tested
{
	if (color == BLACK) // BLACK
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
			cango.push_back({ x - 1, y }); // y == 1 2 0
			if (y != 0) cango.push_back({ x, y - 1 }); // y == 1 2
			if (y != 2) cango.push_back({ x, y + 1 }); // y == 1 0
		}
	}
	else if(color == RED)             // RED
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
	kingKing(cango);
}

void General::board_moveable(int x, int y, vector<Pos>& cango, Chess board[][9])
{
	if (color == BLACK) // BLACK
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
			cango.push_back({ x - 1, y }); // y == 1 2 0
			if (y != 0) cango.push_back({ x, y - 1 }); // y == 1 2
			if (y != 2) cango.push_back({ x, y + 1 }); // y == 1 0
		}
	}
	else if (color == RED)             // RED
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
	board_checkCompanion(cango, board);
	board_kingKing(cango, board);
}

// Advisor
void Advisor::moveable(int x, int y, vector<Pos>& cango) // tested
{
	if (!kingKing(cango))
	{
		if (color == BLACK)   // BLACK	
		{
			if (x != 4)
			{
				cango.push_back({ 4, 1 });
			}
			else
			{
				cango.push_back({ 5, 0 });
				cango.push_back({ 3, 0 });
				cango.push_back({ 5, 2 });
				cango.push_back({ 3, 2 });
			}
		}
		else if(color == RED)             // RED
		{
			if (x != 4)
			{
				cango.push_back({ 4, 8 });
			}
			else
			{
				cango.push_back({ 5, 7 });
				cango.push_back({ 3, 7 });
				cango.push_back({ 5, 9 });
				cango.push_back({ 3, 9 });
			}
		}
		checkCompanion(cango);
	}
}

void Advisor::board_moveable(int x, int y, vector<Pos>& cango, Chess board[][9])
{
	if (!board_kingKing(cango, board))
	{
		if (color == BLACK)   // BLACK	
		{
			if (x != 4)
			{
				cango.push_back({ 4, 1 });
			}
			else
			{
				cango.push_back({ 5, 0 });
				cango.push_back({ 3, 0 });
				cango.push_back({ 5, 2 });
				cango.push_back({ 3, 2 });
			}
		}
		else if (color == RED)             // RED
		{
			if (x != 4)
			{
				cango.push_back({ 4, 8 });
			}
			else
			{
				cango.push_back({ 5, 7 });
				cango.push_back({ 3, 7 });
				cango.push_back({ 5, 9 });
				cango.push_back({ 3, 9 });
			}
		}
		board_checkCompanion(cango, board);
	}
}

// Elephant
void Elephant::moveable(int x, int y, vector<Pos>& cango) // tested
{
	if (!kingKing(cango))
	{
		if (color == BLACK)
		{
			if (x > 1 && y > 1) // left up
			{
				if (Board::getChess(x - 1, y - 1).chess_type == NULL_CHESS) cango.push_back({ x - 2, y - 2 });
			}
			if (x < 7 && y < 3) // right down
			{
				if (Board::getChess(x + 1, y + 1).chess_type == NULL_CHESS) cango.push_back({ x + 2 , y + 2 });
			}
			if (x > 1 && y < 3) // left down
			{
				if (Board::getChess(x - 1, y + 1).chess_type == NULL_CHESS) cango.push_back({ x - 2,  y + 2 });
			}
			if (x < 7 && y > 1) // right up
			{
				if (Board::getChess(x + 1, y - 1).chess_type == NULL_CHESS) cango.push_back({ x + 2,  y - 2 });
			}
		}
		else if (color == RED)
		{
			if (x > 1 && y > 6) // left up
			{
				if (Board::getChess(x - 1, y - 1).chess_type == NULL_CHESS) cango.push_back({ x - 2, y - 2 });
			}
			if (x < 7 && y < 8) // right down
			{
				if (Board::getChess(x + 1, y + 1).chess_type == NULL_CHESS) cango.push_back({ x + 2 , y + 2 });
			}
			if (x > 1 && y < 8) // left down
			{
				if (Board::getChess(x - 1, y + 1).chess_type == NULL_CHESS) cango.push_back({ x - 2,  y + 2 });
			}
			if (x < 7 && y > 6) // right up
			{
				if (Board::getChess(x + 1, y - 1).chess_type == NULL_CHESS) cango.push_back({ x + 2,  y - 2 });
			}
		}
		checkCompanion(cango);
	}
}

void Elephant::board_moveable(int x, int y, vector<Pos>& cango, Chess board[][9])
{
	if (!board_kingKing(cango, board))
	{
		if (color == BLACK)
		{
			if (x > 1 && y > 1) // left up
			{
				if (board[y - 1][x - 1].chess_type == NULL_CHESS) cango.push_back({ x - 2, y - 2 });
			}
			if (x < 7 && y < 3) // right down
			{
				if (board[y + 1][x + 1].chess_type == NULL_CHESS) cango.push_back({ x + 2 , y + 2 });
			}
			if (x > 1 && y < 3) // left down
			{
				if (board[y + 1][x - 1].chess_type == NULL_CHESS) cango.push_back({ x - 2,  y + 2 });
			}
			if (x < 7 && y > 1) // right up
			{
				if (board[y - 1][x + 1].chess_type == NULL_CHESS) cango.push_back({ x + 2,  y - 2 });
			}
		}
		else if (color == RED)
		{
			if (x > 1 && y > 6) // left up
			{
				if (board[y - 1][x - 1].chess_type == NULL_CHESS) cango.push_back({ x - 2, y - 2 });
			}
			if (x < 7 && y < 8) // right down
			{
				if (board[y + 1][x + 1].chess_type == NULL_CHESS) cango.push_back({ x + 2 , y + 2 });
			}
			if (x > 1 && y < 8) // left down
			{
				if (board[y + 1][x - 1].chess_type == NULL_CHESS) cango.push_back({ x - 2,  y + 2 });
			}
			if (x < 7 && y > 6) // right up
			{
				if (board[y - 1][x + 1].chess_type == NULL_CHESS) cango.push_back({ x + 2,  y - 2 });
			}
		}
		board_checkCompanion(cango, board);
	}
}

// Chariot
void Chariot::moveable(int x, int y, vector<Pos>& cango) // tested
{
	if (!kingKing(cango))
	{
		if (y < 9) // go down
		{
			for (int i = y + 1; i < 10; i++)
			{
				cango.push_back({ x, i });
				int chessType = Board::getChess(x, i).chess_type;
				if (chessType != NULL_CHESS)
				{
					break;
				}
			}
		}
		if (y > 0) // go up
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
		if (x < 8) // go right
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
		if (x > 0) // go left
		{
			for (int i = x - 1; i >= 0; i--)
			{
				cango.push_back({ i, y });
				int chessType = Board::getChess(i, y).chess_type;
				if (chessType != NULL_CHESS)                                  // chesstype = NULL_CHESS ?
				{
					break;
				}
			}
		}
		checkCompanion(cango);
	}
}

void Chariot::board_moveable(int x, int y, vector<Pos>& cango, Chess board[][9])
{
	if (!board_kingKing(cango, board))
	{
		if (y < 9) // go down
		{
			for (int i = y + 1; i < 10; i++)
			{
				cango.push_back({ x, i });
				int chessType = board[i][x].chess_type;
				if (chessType != NULL_CHESS)
				{
					break;
				}
			}
		}
		if (y > 0) // go up
		{
			for (int i = y - 1; i >= 0; i--)
			{
				cango.push_back({ x, i });
				int chessType = board[i][x].chess_type;
				if (chessType != NULL_CHESS)
				{
					break;
				}
			}
		}
		if (x < 8) // go right
		{
			for (int i = x + 1; i < 9; i++)
			{
				cango.push_back({ i, y });
				int chessType = board[y][i].chess_type;
				if (chessType != NULL_CHESS)
				{
					break;
				}
			}
		}
		if (x > 0) // go left
		{
			for (int i = x - 1; i >= 0; i--)
			{
				cango.push_back({ i, y });
				int chessType = board[y][i].chess_type;
				if (chessType != NULL_CHESS)                                  // chesstype = NULL_CHESS ?
				{
					break;
				}
			}
		}
		board_checkCompanion(cango, board);
	}
}

// Horse
void Horse::moveable(int x, int y, vector<Pos>& cango) // tested
{
	if (!kingKing(cango))
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
			if (Board::getChess(x, y - 1).chess_type == NULL_CHESS)
			{
				if (x < 8) cango.push_back({ x + 1, y - 2 }); // 上上右
				if (x > 0) cango.push_back({ x - 1, y - 2 }); // 上上左
			}
		}
		if (x < 7)
		{
			if (Board::getChess(x + 1, y).chess_type == NULL_CHESS)
			{
				if (y < 9) cango.push_back({ x + 2, y + 1 }); // 右右下
				if (y > 0) cango.push_back({ x + 2, y - 1 }); // 右右上
			}
		}
		if (x > 1)
		{
			if (Board::getChess(x - 1, y).chess_type == NULL_CHESS)
			{
				if (y < 9) cango.push_back({ x - 2, y + 1 }); // 左左下
				if (y > 0) cango.push_back({ x - 2, y - 1 }); // 左左上
			}
		}
		checkCompanion(cango);
	}
}

void Horse::board_moveable(int x, int y, vector<Pos>& cango, Chess board[][9])
{
	if (!board_kingKing(cango, board))
	{
		if (y < 8)
		{
			if (board[y + 1][x].chess_type == NULL_CHESS)
			{
				if (x < 8) cango.push_back({ x + 1, y + 2 }); // 下下右
				if (x > 0) cango.push_back({ x - 1, y + 2 }); // 下下左
			}
		}
		if (y > 1)
		{
			if (board[y - 1][x].chess_type == NULL_CHESS)
			{
				if (x < 8) cango.push_back({ x + 1, y - 2 }); // 上上右
				if (x > 0) cango.push_back({ x - 1, y - 2 }); // 上上左
			}
		}
		if (x < 7)
		{
			if (board[y][x + 1].chess_type == NULL_CHESS)
			{
				if (y < 9) cango.push_back({ x + 2, y + 1 }); // 右右下
				if (y > 0) cango.push_back({ x + 2, y - 1 }); // 右右上
			}
		}
		if (x > 1)
		{
			if (board[y][x - 1].chess_type == NULL_CHESS)
			{
				if (y < 9) cango.push_back({ x - 2, y + 1 }); // 左左下
				if (y > 0) cango.push_back({ x - 2, y - 1 }); // 左左上
			}
		}
		board_checkCompanion(cango, board);
	}
}

// Cannon
void Cannon::moveable(int x, int y, vector<Pos>& cango) // tested
{
	if (!kingKing(cango))
	{
		vector<Pos> temp;
		if (y < 9) // go down
		{
			for (int i = y + 1; i < 10; i++)
			{
				int chessType = Board::getChess(x, i).chess_type;
				if (chessType != NULL_CHESS)
				{
					for (int j = i + 1; j < 10; j++)
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
		if (y != 0) // go up
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
		if (x < 8) // go right
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
		if (x != 0) // go left
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
}

void Cannon::board_moveable(int x, int y, vector<Pos>& cango, Chess board[][9])
{
	if (!board_kingKing(cango, board))
	{
		vector<Pos> temp;
		if (y < 9) // go down
		{
			for (int i = y + 1; i < 10; i++)
			{
				int chessType = board[i][x].chess_type;
				if (chessType != NULL_CHESS)
				{
					for (int j = i + 1; j < 10; j++)
					{
						chessType = board[j][x].chess_type;
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
		if (y != 0) // go up
		{
			for (int i = y - 1; i >= 0; i--)
			{
				int chessType = board[i][x].chess_type;
				if (chessType != NULL_CHESS)
				{
					for (int j = i - 1; j >= 0; j--)
					{
						chessType = board[j][x].chess_type;
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
		if (x < 8) // go right
		{
			for (int i = x + 1; i < 9; i++)
			{
				int chessType = board[y][i].chess_type;
				if (chessType != NULL_CHESS)
				{
					for (int j = i + 1; j < 9; j++)
					{
						chessType = board[y][j].chess_type;
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
		if (x != 0) // go left
		{
			for (int i = x - 1; i >= 0; i--)
			{
				int chessType = board[y][i].chess_type;
				if (chessType != NULL_CHESS)
				{
					for (int j = i - 1; j >= 0; j--)
					{
						chessType = board[y][j].chess_type;
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
		board_checkCompanion(cango, board);
	}
}

// Soldier
void Soldier::moveable(int x, int y, vector<Pos>& cango) // tested
{
	if (!kingKing(cango))
	{
		if (color == RED)
		{
			if (y > 0) cango.push_back({ x, y - 1 });
			if (y < 5) // cross the river
			{
				if (x < 8) cango.push_back({ x + 1, y });
				if (x > 0) cango.push_back({ x - 1, y });
			}
		}
		else if (color == BLACK)
		{
			if (y < 9) cango.push_back({ x, y + 1 });
			if (y > 4)// cross the river
			{
				if (x < 8) cango.push_back({ x + 1, y });
				if (x > 0) cango.push_back({ x - 1, y });
			}
		}
		checkCompanion(cango);
	}
}

void Soldier::board_moveable(int x, int y, vector<Pos>& cango, Chess board[][9])
{
	if (!board_kingKing(cango, board))
	{
		if (color == RED)
		{
			if (y > 0) cango.push_back({ x, y - 1 });
			if (y < 5) // cross the river
			{
				if (x < 8) cango.push_back({ x + 1, y });
				if (x > 0) cango.push_back({ x - 1, y });
			}
		}
		else if (color == BLACK)
		{
			if (y < 9) cango.push_back({ x, y + 1 });
			if (y > 4)// cross the river
			{
				if (x < 8) cango.push_back({ x + 1, y });
				if (x > 0) cango.push_back({ x - 1, y });
			}
		}
		board_checkCompanion(cango, board);
	}
}