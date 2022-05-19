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

//after move the 2nd movable() is required
bool Chess::checkmate(Pos general_pos, vector<Pos>& oppo_all_chess_cango)
{
	// whether general can escape by himself
	for (auto a : oppo_all_chess_cango)
	{
		if (a == general_pos) // checkmate !!!(delete checkmate() ?
		{
			return true;
		}
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
}

bool Chess::ifMoveThenLose() //need opponent's all_chess_cango and all allys' Pos 
{
	vector<Pos> all_able_to_move_ally_pos; // without our general's pos
	vector<Pos> oppo_all_chess_cango; // for checking if checkmate
	Chess board_for_test[10][9];
	bool general_escape = false;
	int general_type;
	Pos general_pos;
	vector<Pos> general_cango;

	// fill in board_for_test
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			board_for_test[y][x] = Board::getChess(x, y);
		}
	}

	//fill in "all_ally_pos"
	for (pair<Pos, vector<Pos>>& element_of_all_chess_cango : Board::all_chess_cango)
	{
		Chess chess_on_board = Board::getChess(element_of_all_chess_cango.first.x, element_of_all_chess_cango.first.y);
		if (chess_on_board.color != color)
		{
			for (Pos& element : element_of_all_chess_cango.second)
			{
				oppo_all_chess_cango.push_back(element);
			}
		}
		if (chess_on_board.color == color)
		{
			// fill in "all_able_to_move_ally_pos"
			if (chess_on_board.chess_type % 10 != 7 && element_of_all_chess_cango.second.size() != 0) all_able_to_move_ally_pos.push_back(element_of_all_chess_cango.first);
			else if (chess_on_board.chess_type % 10 == 7 && element_of_all_chess_cango.second.size() != 0)
			{
				general_type = chess_on_board.chess_type;
				general_pos = element_of_all_chess_cango.first;
				for (auto& i : element_of_all_chess_cango.second)
				{
					general_cango.push_back(i);
				}
			}
		}
	}

	// whether general can escape by himself
	if(checkmate(general_pos, oppo_all_chess_cango))
	{
		general_escape = gereral_can_escape(board_for_test, general_pos, general_cango, general_type);
		if (general_escape) return false; // 無欠行
	}

	int counter = 0;
	for (auto i : all_able_to_move_ally_pos)
	{
		counter += ifMoveThenLose_simu(board_for_test, i); 
	}

	if (counter == all_able_to_move_ally_pos.size()) return true;
	else return false;
}

bool Chess::gereral_can_escape(Chess board[][9], Pos general_pos, vector<Pos> general_cango, int type)
{
	general_cango.insert(general_cango.begin(), general_pos);
	for (auto& general_cango_element : general_cango)
	{
		// Change the board
		board[general_cango_element.y][general_cango_element.x] = General(general_cango_element.x, general_cango_element.y, type);
		
		// declare
		vector<Pos> oppo_all_chess_cango;
		vector<pair<Pos, vector<Pos>>> all_chess_cango_cver;
		
		// fill in "all_chess_can_go"
		load_all_chess_cango_cver(board, all_chess_cango_cver);

		// fill in " oppo_all_chess_cango"
		for (pair<Pos, vector<Pos>>& element_of_all_chess_cango : all_chess_cango_cver)
		{
			Chess chess_on_board = Board::getChess(element_of_all_chess_cango.first.x, element_of_all_chess_cango.first.y);
			if (chess_on_board.color != color && chess_on_board.color != NULL_COLOR)
			{
				for (Pos& element : element_of_all_chess_cango.second)
				{
					oppo_all_chess_cango.push_back(element);
				}
			}
		}

		// check whether "oppo_all_chess_cango" overlap general's position on the current board
		int counter = 0;
		for (auto& oppo_all_chess_cango_element: oppo_all_chess_cango)
		{
			if (oppo_all_chess_cango_element == general_cango_element) break;
			counter++;
		}

		if (counter == oppo_all_chess_cango.size()) return true;

		board[general_cango_element.y][general_cango_element.x] = Null(general_cango_element.x, general_cango_element.y);
	}
	return false;
}

int Chess::ifMoveThenLose_simu(Chess board[][9], Pos simu)
{
	vector<pair<Pos, vector<Pos>>> all_chess_cango_cver;
	vector<Pos> oppo_all_chess_cango;
	Pos our_general_pos;
	board[simu.y][simu.x] = Null(simu.x, simu.y);
	load_all_chess_cango_cver(board, all_chess_cango_cver);

	//fill in "oppo_all_chess_cango"
	for (pair<Pos, vector<Pos>>& element_of_all_chess_cango : all_chess_cango_cver)
	{
		Chess chess_on_board = Board::getChess(element_of_all_chess_cango.first.x, element_of_all_chess_cango.first.y);
		if (chess_on_board.color != color && chess_on_board.color != NULL_COLOR)
		{
			for (Pos& element : element_of_all_chess_cango.second)
			{
				oppo_all_chess_cango.push_back(element);
			}
		}
		else if ((chess_on_board.color == color) && (chess_on_board.color != NULL_COLOR) && (chess_on_board.chess_type % 10 == 7))
		{
			our_general_pos = { element_of_all_chess_cango.first.x ,element_of_all_chess_cango.first.y };
		}
	}

	int counter = 0;
	for (int i = 0; i < oppo_all_chess_cango.size(); i++)
	{
		if (oppo_all_chess_cango[i] == our_general_pos)
		{
			counter++;
		}
	}

	if (counter == oppo_all_chess_cango.size())
	{
		return 1;
	}

	return 0;
}

void Chess::load_all_chess_cango_cver(Chess board[][9], vector<pair<Pos, vector<Pos>>> a)
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 10; j++) {
			vector<Pos> cango;
			if (board[j][i].chess_type != NULL_CHESS) {
				useChess_cver(board[j][i], cango);
				a.push_back({ Pos(i,j), cango });
				/*
				cout << j << ',' << i << ' ';
				for (int x = 0; x < cango.size(); x++) cout << cango[x].x << ',' << cango[x].y << ' ';
				cout << '\n';
				*/
			}
		}
	}
}

void Chess::useChess_cver(Chess& temp_chess, vector<Pos>& cango) {
	int x = temp_chess.pos.x, y = temp_chess.pos.y;
	if (temp_chess.chess_type % 10 == GENERAL) {
		General general(x, y, temp_chess.chess_type);
		general.moveable(x, y, cango);
	}
	else if (temp_chess.chess_type % 10 == ADVISOR) {
		Advisor advisor(x, y, temp_chess.chess_type);
		advisor.moveable(x, y, cango);
	}
	else if (temp_chess.chess_type % 10 == ELEPHANT) {
		Elephant elephant(x, y, temp_chess.chess_type);
		elephant.moveable(x, y, cango);
	}
	else if (temp_chess.chess_type % 10 == CHARIOT) {
		Chariot chariot(x, y, temp_chess.chess_type);
		chariot.moveable(x, y, cango);
	}
	else if (temp_chess.chess_type % 10 == HORSE) {
		Horse horse(x, y, temp_chess.chess_type);
		horse.moveable(x, y, cango);
	}
	else if (temp_chess.chess_type % 10 == CANNON) {
		Cannon cannon(x, y, temp_chess.chess_type);
		cannon.moveable(x, y, cango);
	}
	else if (temp_chess.chess_type % 10 == SOLDIER) {
		Soldier soldier(x, y, temp_chess.chess_type);
		soldier.moveable(x, y, cango);
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
			cango.push_back({ y,x - 1 }); // y == 1 2 0
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
				if (x < 9) cango.push_back({ x + 1, y });
				if (x > 0) cango.push_back({ x - 1, y });
			}
		}
		else if (color == BLACK)
		{
			if (y < 9) cango.push_back({ x, y + 1 });
			if (y > 4)// cross the river
			{
				if (x < 9) cango.push_back({ x + 1, y });
				if (x > 0) cango.push_back({ x - 1, y });
			}
		}
		checkCompanion(cango);
	}
}