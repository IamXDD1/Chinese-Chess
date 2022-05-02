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

	virtual void moveable(int x, int y, vector<pair<int, int>>& cango) = 0;  // Gabriel
	virtual bool move(int x, int y) = 0;
	virtual bool checkmate(int x, int y) = 0;
};

class General : public Chess {
public:
	General(int x, int y, int player) : Chess() {
		pos.x = x;
		pos.y = y;
		color = player;
	}
	void moveable(int x, int y, vector<pair<int, int>>& cango) {}
	bool move(int x, int y) {}
	bool checkmate(int x, int y) {}
};

class Advisor : public Chess {
public:
	Advisor(int x, int y, int player) : Chess() {
		pos.x = x;
		pos.y = y;
		color = player;
	}
	void moveable(int x, int y, vector<pair<int, int>>& cango) {}
	bool move(int x, int y) {}
	bool checkmate(int x, int y) {}
};

class Elephant : public Chess {
public:
	Elephant(int x, int y, int player) : Chess() {
		pos.x = x;
		pos.y = y;
		color = player;
	}
	void moveable(int x, int y, vector<pair<int, int>>& cango) {}
	bool move(int x, int y) {}
	bool checkmate(int x, int y) {}
};

class Chariot : public Chess {
public:
	Chariot(int x, int y, int player) : Chess() {
		pos.x = x;
		pos.y = y;
		color = player;
	}
	void moveable(int x, int y, vector<pair<int, int>>& cango) {}
	bool move(int x, int y) {}
	bool checkmate(int x, int y) {}
};

class Horse : public Chess {
public:
	Horse(int x, int y, int player) : Chess() {
		pos.x = x;
		pos.y = y;
		color = player;
	}
	void moveable(int x, int y, vector<pair<int, int>>& cango) {}
	bool move(int x, int y) {}
	bool checkmate(int x, int y) {}
};

class Cannon : public Chess {
public:
	Cannon(int x, int y, int player) : Chess() {
		pos.x = x;
		pos.y = y;
		color = player;
	}
	void moveable(int x, int y, vector<pair<int, int>>& cango) {
		bool object = false;
		for (int i = 0; i < 9; i++) {
			if (object) {
				if (move(i, pos.y) == false) {
					cango.push_back({ i,pos.y });
				}
			}
			else if (move(i, pos.y)) {
				cango.push_back({ i,pos.y });
			}
			else {
				object = true;
			}
		}
		return;
	}
	bool move(int x, int y) {
		return true;
	}
	bool checkmate(int x, int y) {
		return true;
	}
};

class Soldier : public Chess {
public:
	Soldier(int x, int y, int player) : Chess() {
		pos.x = x;
		pos.y = y;
		color = player;
	}
	void moveable(int x, int y, vector<pair<int, int>>& cango) {}
	bool move(int x, int y) {}
	bool checkmate(int x, int y) {}
};