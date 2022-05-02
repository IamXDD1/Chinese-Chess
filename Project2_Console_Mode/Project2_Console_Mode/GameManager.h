#pragma once
#include <fstream>
#include <vector>
#include <string>
#include "Chess.h"

#define BLACK 0
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
			board[i] = new int[9];
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
	vector<string> Input();  //XDD
	void Output();
};

class GameManager : public Board {
	vector<Chess> on_board;
	int current_player;
	Board gameBoard;
	Viewer viewer;
public:
	int checkChess(int x, int y) {
		vector<pair<int, int>> cango;
		switch (gameBoard.board[y][x])
		{
			case GENERAL:
				General general(x, y, current_player);
				general.moveable(x, y, cango);
				break;
			case ADVISOR:
				Advisor advisor(x, y, current_player);
				advisor.moveable(x, y, cango);
				break;
			case ELEPHANT:
				Elephant elephant(x, y, current_player);
				elephant.moveable(x, y, cango);
				break;
			case CHARIOT:
				Chariot chariot(x, y, current_player);
				chariot.moveable(x, y, cango);
				break;
			case HORSE:
				Horse horse(x, y, current_player);
				horse.moveable(x, y, cango);
				break;
			case CANNON: 
				Cannon cannon(x, y, current_player);
				cannon.moveable(x, y, cango);
				break;
			case SOLDIER:
				Soldier soldier(x, y, current_player);
				soldier.moveable(x, y, cango);
				break;
		default:
			break;
		}
	}

	bool endGame();
	
};
