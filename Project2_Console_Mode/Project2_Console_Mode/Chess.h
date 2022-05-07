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
	bool death;
	int color;
public:
	Chess() {
		pos.x = 0;
		pos.y = 0;
		bool death = false;
		color = -1;
	};

	virtual void moveable(int x, int y, int num, vector<pair<int, int>>& cango, Board board) {};  // Gabriel
	virtual vector<pair<int, int>> checkCompanion(int type, vector<pair<int, int>>& cango,Board board);
	virtual void move(int x, int y);
	virtual void checkDeath(int x, int y);
	virtual bool checkmate(int x, int y) = 0;
};

class General : public Chess {
public:
	General(int x, int y, int player) : Chess() {
		pos.x = x;
		pos.y = y;
		color = player;
	}
	void moveable(int x, int y, int num, vector<pair<int, int>>& cango, Board board);
	void move(int x, int y);
	bool checkmate(int x, int y);
};

class Advisor : public Chess {
public:
	Advisor(int x, int y, int player) : Chess() {
		pos.x = x;
		pos.y = y;
		color = player;
	}
	void moveable(int x, int y, int num, vector<pair<int, int>>& cango, Board board);
	bool checkmate(int x, int y);
};

class Elephant : public Chess {
public:
	Elephant(int x, int y, int player) : Chess() {
		pos.x = x;
		pos.y = y;
		color = player;
	}
	void moveable(int x, int y, int num, vector<pair<int, int>>& cango, Board board);
	bool checkmate(int x, int y);
};

class Chariot : public Chess {
public:
	Chariot(int x, int y, int player) : Chess() {
		pos.x = x;
		pos.y = y;
		color = player;
	}
	void moveable(int x, int y, int num, vector<pair<int, int>>& cango, Board board);
	bool checkmate(int x, int y);
};

class Horse : public Chess {
public:
	Horse(int x, int y, int player) : Chess() {
		pos.x = x;
		pos.y = y;
		color = player;
	}
	void moveable(int x, int y, int num, vector<pair<int, int>>& cango, Board board);
	bool checkmate(int x, int y);
};

class Cannon : public Chess {
public:
	Cannon(int x, int y, int player) : Chess() {
		pos.x = x;
		pos.y = y;
		color = player;
	}
	void moveable(int x, int y, int num, vector<pair<int, int>>& cango, Board board);
	bool checkmate(int x, int y);
};

class Soldier : public Chess {
public:
	Soldier(int x, int y, int player) : Chess() {
		pos.x = x;
		pos.y = y;
		color = player;
	}
	void moveable(int x, int y, int num, vector<pair<int, int>>& cango, Board board);
	bool checkmate(int x, int y);
};