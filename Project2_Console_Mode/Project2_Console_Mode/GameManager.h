#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Chess.h"
#include "Clock.h"

#define BLACK 2
#define RED 1

#define BLACK_GENERAL	7
#define BLACK_ADVISOR	6
#define BLACK_ELEPHANT	5
#define BLACK_CHARIOT	4
#define BLACK_HORSE		3
#define BLACK_CANNON	2
#define BLACK_SOLDIER	1

#define RED_GENERAL		17
#define RED_ADVISOR		16
#define RED_ELEPHANT	15
#define RED_CHARIOT		14
#define RED_HORSE		13
#define RED_CANNON		12
#define RED_SOLDIER		11

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
	bool Load(vector<string>& data) {  //XDD
		file.open(filename);
		if (!file) {
			cout << "File \"" + filename + "\" can't be opened.\n";
			return false;
		}
		else {
			string temp;
			for (; getline(file, temp);) {
				data.push_back(temp);
				gameRecord.push_back(temp);
			}
			return true;
		}
	}
	void Input(string& data, int& color, string& character, int& x1, int& y1, int& x2, int& y2) {
		stringstream ss(data);
		string part;
		bool player = false;
		bool action = false;
		int action_count = 0;
		for (; ss >> part;) {
			if (part == "Player:") {
				player = true;
				action = false;
				continue;
			}
			else if (part == "Action:") {
				player = false;
				action = true;
				continue;
			}

			if (player) {
				if (part[0] - '0' == BLACK) color = BLACK;
				else if (part[0] - '0' == RED) color = RED;
				else throw "Player doesn't exist.";
			}
			else if (action) {
				action_count++;
				switch (action_count)
				{
				case 1:	character = part; break;
				case 2: x1 = part[1] - '0'; break;
				case 3: y1 = part[0] - '0'; break;
				case 5: x2 = part[1] - '0'; break;
				case 6: y2 = part[0] - '0'; break;
				}
			}
		}
	}
	inline void Output() {
		for (int i = 0; i < gameRecord.size(); i++)
			file << gameRecord[i] << '\n';
	}
	inline void closeFile() { file.close(); }
};

class Board {
protected:
	int** board;
public:
	Board() {
		board = new int* [10];
		for (int i = 0; i < 10; i++) {
			board[i] = new int[9]{};
		}
		initialization(board);
	}

	void initialization(int** board) {
		board[0][0] = board[0][8] = BLACK_CHARIOT; board[9][0] = board[9][8] = RED_CHARIOT;
		board[0][1] = board[0][7] = BLACK_HORSE; board[9][1] = board[9][7] = RED_HORSE;
		board[0][2] = board[0][6] = BLACK_ELEPHANT; board[9][2] = board[9][6] = RED_ELEPHANT;
		board[0][3] = board[0][5] = BLACK_ADVISOR; board[9][3] = board[9][5] = RED_ADVISOR;
		board[0][4] = BLACK_GENERAL; board[9][4] = RED_GENERAL;
		board[2][1] = board[2][7] = BLACK_CANNON; board[7][1] = board[7][7] = RED_CANNON;
		board[3][0] = board[3][2] = board[3][4] = board[3][6] = board[3][8] = BLACK_SOLDIER;
		board[6][0] = board[6][2] = board[6][4] = board[6][6] = board[6][8] = RED_SOLDIER;
		return;
	}
	int getChess(int& x, int& y) { return board[y][x]; }
	bool checkChess(int chess, int& color, string& character) {
		switch (chess)
		{
		case BLACK_GENERAL: if (color == BLACK && character == "General") return true; break;
		case RED_GENERAL:	if (color == RED && character == "General") return true; break;
		case BLACK_ADVISOR: if (color == BLACK && character == "Advisor") return true; break;
		case RED_ADVISOR:	if (color == RED && character == "Advisor") return true;; break;
		case BLACK_ELEPHANT:if (color == BLACK && character == "Elephant") return true; break;
		case RED_ELEPHANT:	if (color == RED && character == "Elephant") return true; break;
		case BLACK_CHARIOT: if (color == BLACK && character == "Chariot") return true; break;
		case RED_CHARIOT:	if (color == RED && character == "Chariot") return true; break;
		case BLACK_HORSE:	if (color == BLACK && character == "Horse") return true; break;
		case RED_HORSE:		if (color == RED && character == "Horse") return true; break;
		case BLACK_CANNON:	if (color == BLACK && character == "Cannon") return true; break;
		case RED_CANNON:	if (color == RED && character == "Cannon") return true; break;
		case BLACK_SOLDIER: if (color == BLACK && character == "Soldier") return true; break;
		case RED_SOLDIER:	if (color == RED && character == "Soldier") return true; break;
		default:
			return false;
			break;
		}
	}
	void moveChess(File& file, int& color, string& character, int& x1, int& y1, int& x2, int& y2) {
		if (checkChess(board[y1][x1], color, character)) {
			board[y2][x2] = board[y1][x1];  //move
			board[y1][x1] = 0;
			string str = "Player: " + to_string(color) + ", Action: " + character +
				" (" + to_string(x1) + ", " + to_string(y1) + ") -> (" + to_string(x2) + ", " + to_string(y2) + ")     \n";
			file.gameRecord.push_back(str);
			cout << str;
		}
		else throw "Move chess fail, for wrong color or chess";
	}
	void showBoard() {
		gotoxy(0, 0);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 9; j++) {
				switch (board[i][j]) {
				case 0: cout << "　"; break;
				case BLACK_GENERAL: cout << "將"; break;
				case RED_GENERAL:	cout << "帥"; break;
				case BLACK_ADVISOR: cout << "士"; break;
				case RED_ADVISOR:	cout << "仕"; break;
				case BLACK_ELEPHANT:cout << "象"; break;
				case RED_ELEPHANT:	cout << "相"; break;
				case BLACK_CHARIOT: cout << "車"; break;
				case RED_CHARIOT:	cout << "車"; break;
				case BLACK_HORSE:	cout << "馬"; break;
				case RED_HORSE:		cout << "傌"; break;
				case BLACK_CANNON:	cout << "砲"; break;
				case RED_CANNON:	cout << "炮"; break;
				case BLACK_SOLDIER: cout << "卒"; break;
				case RED_SOLDIER:	cout << "兵"; break;
				}
			}
			cout << '\n';
		}
	}
	~Board() {
		for (int i = 0; i < 10; i++) {
			delete[] board[i];
		}
		delete[] board;
	}
};

class GameManager {
public:
	vector<Chess> on_board;
	int current_player;
	Board gameBoard;
	Viewer viewer;
	int checkChess(int x, int y) {
		vector<pair<int, int>> cango;
		int chess_type = gameBoard.getChess(x, y);
		if (chess_type == BLACK_GENERAL || chess_type == RED_GENERAL) {
			General general(x, y, current_player);
			general.moveable(x, y, chess_type, cango, gameBoard);
		}
		else if (chess_type == BLACK_ADVISOR || chess_type == RED_ADVISOR) {
			Advisor advisor(x, y, current_player);
			advisor.moveable(x, y, chess_type, cango, gameBoard);
		}
		else if (chess_type == BLACK_ELEPHANT || chess_type == RED_ELEPHANT) {
			Elephant elephant(x, y, current_player);
			elephant.moveable(x, y, chess_type, cango, gameBoard);
		}
		else if (chess_type == BLACK_CHARIOT || chess_type == RED_CHARIOT) {
			Chariot chariot(x, y, current_player);
			chariot.moveable(x, y, chess_type, cango, gameBoard);
		}
		else if (chess_type == BLACK_HORSE || chess_type == RED_HORSE) {
			Horse horse(x, y, current_player);
			horse.moveable(x, y, chess_type, cango, gameBoard);
		}
		else if (chess_type == BLACK_CANNON || chess_type == RED_CANNON) {
			Cannon cannon(x, y, current_player);
			cannon.moveable(x, y, chess_type, cango, gameBoard);
		}
		else if (chess_type == BLACK_SOLDIER || chess_type == RED_SOLDIER) {
			Soldier soldier(x, y, current_player);
			soldier.moveable(x, y, chess_type, cango, gameBoard);
		}
	}

	bool endGame();

};