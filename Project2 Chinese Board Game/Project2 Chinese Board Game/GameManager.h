#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Clock.h"
#include "Chess.h"

#define BLACK 2
#define RED 1

#define BLACK_GENERAL	27
#define BLACK_ADVISOR	26
#define BLACK_ELEPHANT	25
#define BLACK_CHARIOT	24
#define BLACK_HORSE		23
#define BLACK_CANNON	22
#define BLACK_SOLDIER	21

#define RED_GENERAL		17
#define RED_ADVISOR		16
#define RED_ELEPHANT	15
#define RED_CHARIOT		14
#define RED_HORSE		13
#define RED_CANNON		12
#define RED_SOLDIER		11

#define GENERAL		7
#define ADVISOR		6
#define ELEPHANT	5
#define CHARIOT		4
#define HORSE		3
#define CANNON		2
#define SOLDIER		1
#define NULL_CHESS -1

using namespace std;

class Viewer {
	int player;
public:
	Viewer() { player = RED; }

};

class File {
	fstream file;
	string filename;
public:
	vector<string> gameRecord;
	File() : filename("") {};
	inline void setFilename(string name) { filename = name; }
	bool Load(vector<string>& data);
	void Input(string data, int& color, string& character, int& x1, int& y1, int& x2, int& y2);
	void Output();
	inline string getFilename() { return filename; }
	inline void closeFile() { file.close(); }
};

class Board {
protected:
	static Chess board[10][9];

	static int ifMoveThenLose_simu(Chess board[][9], pair<Pos, vector<Pos>> simu, int color);
	static void load_all_chess_cango_test(Chess board[][9], vector<pair<Pos, vector<Pos>>>& a);
	static bool gereral_can_escape(Chess board[][9], Pos general_pos, vector<Pos> general_cango,
		vector<pair<Pos, vector<Pos>>> ally_all_chess_cango, int color);
	static bool checkmate(Pos general_pos, vector<Pos>& oppo_all_chess_cango, bool& checkmate);
public:
	static vector<pair<Pos, vector<Pos>>> all_chess_cango;
	Board();
	void initialization();
	static Chess getChess(int x, int y) { return board[y][x]; }
	bool checkChess(Chess chess);
	void moveChess(File* file, int x1, int y1, int x2, int y2, bool loading = false);
	static void useChess(Chess& temp_chess, vector<Pos>& cango);
	void showPath(vector<Pos>& cango);
	bool checkcango(int x2, int y2, vector<Pos> cango);
	void showBoard();
	void showallPath();
	string chessname(int num);

	static void load_all_chess_cango();
	static bool ifMoveThenLose(bool& isCheckmate, int color);
	~Board() {};
};

class GameManager {
public:
	vector<Chess> on_board;
	int current_player;
	Board gameBoard;
	Viewer viewer;

	bool endGame();

};