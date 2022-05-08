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
		cout << data;
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
		if (x1 == -1 || x2 == -1 || y1 == -1 || y2 == -1 || color == -1 || character == "") {
			cout << x1 << ' ' << x2 << ' ' << y1 << ' ' << y2 << ' ' << color << ' ' << character << '\n';
			throw "Wrong input format.";
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
	Chess** board;
public:
	Board() {
		board = new Chess* [10];
		for (int i = 0; i < 10; i++) {
			board[i] = new Chess[9]{};
		}
		initialization(board);
	}
	void initialization(Chess** board) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 9; j++) {
				board[i][j] = Null(i,j);
			}
		}

		board[0][0] = Chariot(0, 0, BLACK_CHARIOT); board[0][8] = Chariot(0, 8, BLACK_CHARIOT); 
		board[9][0] = Chariot(9, 0, RED_CHARIOT);   board[9][8] = Chariot(9, 8, RED_CHARIOT);
		board[0][1] = Horse(0, 1, BLACK_HORSE); board[0][7] = Horse(0, 7, BLACK_HORSE); 
		board[9][1] = Horse(9, 1, RED_HORSE);   board[9][7] = Horse(9, 7, RED_HORSE);
		board[0][2] = Elephant(0, 2, BLACK_ELEPHANT); board[0][6] = Elephant(0, 6, BLACK_ELEPHANT);
		board[9][2] = Elephant(9, 2, RED_ELEPHANT);	  board[9][6] = Elephant(9, 6, RED_ELEPHANT);
		board[0][3] = Advisor(0, 3, BLACK_ADVISOR); board[0][5] = Advisor(0, 5, BLACK_ADVISOR);
		board[9][3] = Advisor(9, 3, RED_ADVISOR);   board[9][5] = Advisor(9, 5, RED_ADVISOR);
		board[0][4] = General(0, 4, BLACK_GENERAL); board[9][4] = General(9, 4, RED_GENERAL);
		board[2][1] = Cannon(2, 1, BLACK_CANNON); board[2][7] = Cannon(2, 7, BLACK_CANNON);
		board[7][1] = Cannon(7, 1, RED_CANNON);   board[7][7] = Cannon(7, 7, RED_CANNON);
		board[3][0] = Soldier(3, 0, BLACK_SOLDIER); board[3][2] = Soldier(3, 2, BLACK_SOLDIER); board[3][4] = Soldier(3, 4, BLACK_SOLDIER);
		board[3][6] = Soldier(3, 6, BLACK_SOLDIER); board[3][8] = Soldier(3, 8, BLACK_SOLDIER);
		board[6][0] = Soldier(6, 0, RED_SOLDIER); board[6][2] = Soldier(6, 2, RED_SOLDIER); board[6][4] = Soldier(6, 4, RED_SOLDIER);
		board[6][6] = Soldier(6, 6, RED_SOLDIER); board[6][8] = Soldier(6, 8, RED_SOLDIER);
		return;
	}
	Chess getChess(int& x, int& y) { return board[y][x]; }
	bool checkChess(Chess chess, int& color, string& character) {
		switch (chess.chess_type)
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
		if (checkChess(getChess(x1,y1), color, character)) {
			board[y2][x2] = board[y1][x1];  //move
			board[y1][x1] = Null(x1, y1);
			string str = "Player: " + to_string(color) + ", Action: " + character + 
				" (" + to_string(x1) + ", " + to_string(y1) + ") -> (" + to_string(x2) + ", " + to_string(y2) + ")     \n";
			file.gameRecord.push_back(str);
			gotoxy(20, 3);
			cout << str;
		}
		else throw "Move chess fail, for wrong color or chess";
	}
	void showBoard() {
		gotoxy(0, 0);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 9; j++) {
				switch (board[i][j].chess_type) {
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
				default: cout << "　"; break;
				}
			}
			cout << '\n';
		}
	}
	~Board() {
		for (int i = 0; i < 10; i++) {
			delete [] board[i];
		}
		delete[] board;
	}
};

class GameManager{
public:
	vector<Chess> on_board;
	int current_player;
	Board gameBoard;
	Viewer viewer;
	int checkChess(int x, int y) {
		vector<pair<int, int>> cango;
		Chess chess = gameBoard.getChess(x, y);
		if (chess.chess_type == BLACK_GENERAL || chess.chess_type == RED_GENERAL) {
			General general(x, y, current_player);
			general.moveable(x, y, cango);
		}
		else if (chess.chess_type == BLACK_ADVISOR || chess.chess_type == RED_ADVISOR) {
			Advisor advisor(x, y, current_player);
			advisor.moveable(x, y, cango);
		}
		else if (chess.chess_type == BLACK_ELEPHANT || chess.chess_type == RED_ELEPHANT) {
			Elephant elephant(x, y, current_player);
			elephant.moveable(x, y, cango);
		}
		else if (chess.chess_type == BLACK_CHARIOT || chess.chess_type == RED_CHARIOT) {
			Chariot chariot(x, y, current_player);
			chariot.moveable(x, y, cango);
		}
		else if (chess.chess_type == BLACK_HORSE || chess.chess_type == RED_HORSE) {
			Horse horse(x, y, current_player);
			horse.moveable(x, y, cango);
		}
		else if (chess.chess_type == BLACK_CANNON || chess.chess_type == RED_CANNON) {
			Cannon cannon(x, y, current_player);
			cannon.moveable(x, y, cango);
		}
		else if (chess.chess_type == BLACK_SOLDIER || chess.chess_type == RED_SOLDIER) {
			Soldier soldier(x, y, current_player);
			soldier.moveable(x, y, cango);
		}
	}

	bool endGame();
	
};
