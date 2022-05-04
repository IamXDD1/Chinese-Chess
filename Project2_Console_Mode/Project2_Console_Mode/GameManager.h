#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Chess.h"

#define BLACK 2
#define RED 1

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

class Board {
public:
	int** board;
	Board() {
		board = new int* [10];
		for (int i = 0; i < 10; i++) {
			board[i] = new int[9]{};
		}
		initialization(board);
	}
	void initialization(int** board) {
		board[0][0] = board[0][8] = board[9][0] = board[9][8] = CHARIOT;
		board[0][1] = board[0][7] = board[9][1] = board[9][7] = HORSE;
		board[0][2] = board[0][6] = board[9][2] = board[9][6] = ELEPHANT;
		board[0][3] = board[0][5] = board[9][3] = board[9][5] = ADVISOR;
		board[0][4] = board[9][4] = GENERAL;
		board[2][1] = board[2][7] = board[7][1] = board[7][7] = CANNON;
		board[3][0] = board[3][2] = board[3][4] = board[3][6] = board[3][8] 
			= board[6][0] = board[6][2] = board[6][4] = board[6][6] = board[6][8] = SOLDIER;
		return;
	}
	void showBoard() {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 9; j++) {
				cout << board[i][j];
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

class File {
	fstream file;
	string filename;
	File() : filename("") {};
	inline void setFilename(string name) { filename = name; }
	void Load(vector<string>& data) {  //XDD
		file.open(filename);
		if (!file) throw "File \"" + filename + "\" can't be opened.";
		else {
			string temp;
			for (; getline(file, temp);) {
				data.push_back(temp);
			}
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
			}
			else if (part == "Action:") {
				player = false;
				action = true;
			}

			if (player) {
				if (data[0] == BLACK) color = BLACK;
				else if (data[0] == RED) color = RED;
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
	inline void Output(string& data) { file << data; }
	inline void closeFile() { file.close(); }
};

class GameManager : public Board {
	vector<Chess> on_board;
	int current_player;
	Board gameBoard;
	Viewer viewer;
public:
	int checkChess(int x, int y) {
		vector<pair<int, int>> cango;
		int chess_type = gameBoard.board[y][x];
		if (chess_type == GENERAL) {
			General general(x, y, current_player);
			general.moveable(x, y, cango);
		}
		else if (chess_type == ADVISOR) {
			Advisor advisor(x, y, current_player);
			advisor.moveable(x, y, cango);
		}
		else if (chess_type == ELEPHANT) {
			Elephant elephant(x, y, current_player);
			elephant.moveable(x, y, cango);
		}
		else if (chess_type == CHARIOT) {
			Chariot chariot(x, y, current_player);
			chariot.moveable(x, y, cango);
		}
		else if (chess_type == HORSE) {
			Horse horse(x, y, current_player);
			horse.moveable(x, y, cango);
		}
		else if (chess_type == CANNON) {
			Cannon cannon(x, y, current_player);
			cannon.moveable(x, y, cango);
		}
		else if (chess_type == SOLDIER) {
			Soldier soldier(x, y, current_player);
			soldier.moveable(x, y, cango);
		}
	}

	bool endGame();
	
};
