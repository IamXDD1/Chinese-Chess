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

	bool operator == (Pos a) {
		if (x == a.x && y == a.y) return true;
		return false;
	}
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

	virtual void moveable(int x, int y, vector<pair<int, int>>& cango) { return; };  // Gabriel
	virtual bool move(int x, int y) { return false; };
	virtual bool checkmate(int x, int y) { return false; };
};

class Null : public Chess {
public:
	Null(int x, int y) : Chess() {
		pos.x = x;
		pos.y = y;
	}
	void moveable(int x, int y, vector<pair<int, int>>& cango) { return; }
	bool move(int x, int y) { return false; }
	bool checkmate(int x, int y) { return false; }
};

class General : public Chess {
public:
	General(int x, int y, int type) : Chess() {
		pos.x = x;
		pos.y = y;
		color = type/10;
		chess_type = type;
	}
	void moveable(int x, int y, vector<pair<int, int>>& cango) {}
	bool move(int x, int y) { return false; }
	bool checkmate(int x, int y) { return false; }
};

class Advisor : public Chess {
public:
	Advisor(int x, int y, int type) : Chess() {
		pos.x = x;
		pos.y = y;
		color = type / 10;
		chess_type = type;
	}
	void moveable(int x, int y, vector<pair<int, int>>& cango) {}
	bool move(int x, int y) { return false; }
	bool checkmate(int x, int y) { return false; }
};

class Elephant : public Chess {
public:
	Elephant(int x, int y, int type) : Chess() {
		pos.x = x;
		pos.y = y;
		color = type / 10;
		chess_type = type;
	}
	void moveable(int x, int y, vector<pair<int, int>>& cango) {}
	bool move(int x, int y) { return false; }
	bool checkmate(int x, int y) { return false; }
};

class Chariot : public Chess {
public:
	Chariot(int x, int y, int type) : Chess() {
		pos.x = x;
		pos.y = y;
		color = type / 10;
		chess_type = type;
	}
	void moveable(int x, int y, vector<pair<int, int>>& cango) {}
	bool move(int x, int y) { return false; }
	bool checkmate(int x, int y) { return false; }
};

class Horse : public Chess {
public:
	Horse(int x, int y, int type) : Chess() {
		pos.x = x;
		pos.y = y;
		color = type / 10;
		chess_type = type;
	}
	void moveable(int x, int y, vector<pair<int, int>>& cango) {}
	bool move(int x, int y) { return false; }
	bool checkmate(int x, int y) { return false; }
};

class Cannon : public Chess {
public:
	Cannon(int x, int y, int type) : Chess() {
		pos.x = x;
		pos.y = y;
		color = type / 10;
		chess_type = type;
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
	bool move(int x, int y) { return false; }
	bool checkmate(int x, int y) { return false; }
};

class Soldier : public Chess {
public:
	Soldier(int x, int y, int type) : Chess() {
		pos.x = x;
		pos.y = y;
		color = type / 10;
		chess_type = type;
	}
	void moveable(int x, int y, vector<pair<int, int>>& cango) {}
	bool move(int x, int y) { return false; }
	bool checkmate(int x, int y) { return false; }
};