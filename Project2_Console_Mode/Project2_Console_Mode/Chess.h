#pragma once
#define BLACK 0
#define RED 1
#include <vector>
#include <algorithm>

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
	virtual bool kingKing(vector<Pos>& cango); // ¤ý¤£¨£¤ý
	virtual int getColor() { return color; }
	vector<Pos> moveable(int x, int y, vector<Pos>& cango) { return cango; };
	void checkCompanion(vector<Pos>& cango);
	virtual bool checkmate(int x, int y, vector<Pos>& cango);
};

class Null : public Chess {
public:
	Null(int x, int y) : Chess() {
		pos.x = x;
		pos.y = y;
	}
};

class General : public Chess {
public:
	General(int x, int y, int type) : Chess() {
		pos.x = x;
		pos.y = y;
		color = type / 10;
		chess_type = type;
	}
	vector<Pos> moveable(int x, int y, vector<Pos>& cango);
};

class Advisor : public Chess {
public:
	Advisor(int x, int y, int type) : Chess() {
		pos.x = x;
		pos.y = y;
		color = type / 10;
		chess_type = type;
	}
	vector<Pos> moveable(int x, int y, vector<Pos>& cango);
};

class Elephant : public Chess {
public:
	Elephant(int x, int y, int type) : Chess() {
		pos.x = x;
		pos.y = y;
		color = type / 10;
		chess_type = type;
	}
	vector<Pos> moveable(int x, int y, vector<Pos>& cango);
};

class Chariot : public Chess {
public:
	Chariot(int x, int y, int type) : Chess() {
		pos.x = x;
		pos.y = y;
		color = type / 10;
		chess_type = type;
	}
	vector<Pos> moveable(int x, int y, vector<Pos>& cango);
};

class Horse : public Chess {
public:
	Horse(int x, int y, int type) : Chess() {
		pos.x = x;
		pos.y = y;
		color = type / 10;
		chess_type = type;
	}
	vector<Pos> moveable(int x, int y, vector<Pos>& cango);
};

class Cannon : public Chess {
public:
	Cannon(int x, int y, int type) : Chess() {
		pos.x = x;
		pos.y = y;
		color = type / 10;
		chess_type = type;
	}
	vector<Pos> moveable(int x, int y, vector<Pos>& cango);
};

class Soldier : public Chess {
public:
	Soldier(int x, int y, int type) : Chess() {
		pos.x = x;
		pos.y = y;
		color = type / 10;
		chess_type = type;
	}
	vector<Pos> moveable(int x, int y, vector<Pos>& cango);
};