#pragma once
#define BLACK 0
#define RED 1
#include <vector>
#include <algorithm>
#include "GameManager.h"

using namespace std;

struct Pos {
	int x;
	int y;
};

class Chess {
protected:
	Pos pos;
	int color;
public:
	int chess_type;
	Chess() {
		pos.x = 0;
		pos.y = 0;
		color = -1;
		chess_type = -1;
	}

	virtual vector<pair<int, int>> moveable(int x, int y, int num, vector<pair<int, int>>& cango, Board board) {};  // Gabriel
	vector<pair<int, int>> checkCompanion(int type, vector<pair<int, int>>& cango, Board board);
	void move(int x, int y, Board board);
	virtual void checkDeath(int x, int y, Board board);
	virtual bool checkmate(int x, int y, Board board);
};


class General : public Chess {
public:
	General(int x, int y, int player) : Chess() {
		pos.x = x;
		pos.y = y;
		color = player;
	}
	vector<pair<int, int>> moveable(int x, int y, int num, vector<pair<int, int>>& cango, Board board);
};

class Advisor : public Chess {
public:
	Advisor(int x, int y, int player) : Chess() {
		pos.x = x;
		pos.y = y;
		color = player;
	}
	vector<pair<int, int>> moveable(int x, int y, int num, vector<pair<int, int>>& cango, Board board);
};

class Elephant : public Chess {
public:
	Elephant(int x, int y, int player) : Chess() {
		pos.x = x;
		pos.y = y;
		color = player;
	}
	vector<pair<int, int>> moveable(int x, int y, int num, vector<pair<int, int>>& cango, Board board);
};

class Chariot : public Chess {
public:
	Chariot(int x, int y, int player) : Chess() {
		pos.x = x;
		pos.y = y;
		color = player;
	}
	vector<pair<int, int>> moveable(int x, int y, int num, vector<pair<int, int>>& cango, Board board);
};

class Horse : public Chess {
public:
	Horse(int x, int y, int player) : Chess() {
		pos.x = x;
		pos.y = y;
		color = player;
	}
	vector<pair<int, int>> moveable(int x, int y, int num, vector<pair<int, int>>& cango, Board board);
	bool checkmate(int x, int y);
};

class Cannon : public Chess {
public:
	Cannon(int x, int y, int player) : Chess() {
		pos.x = x;
		pos.y = y;
		color = player;
	}
	vector<pair<int, int>> moveable(int x, int y, int num, vector<pair<int, int>>& cango, Board board);
};

class Soldier : public Chess {
public:
	Soldier(int x, int y, int player) : Chess() {
		pos.x = x;
		pos.y = y;
		color = player;
	}
	vector<pair<int, int>> moveable(int x, int y, int num, vector<pair<int, int>>& cango, Board board);
};