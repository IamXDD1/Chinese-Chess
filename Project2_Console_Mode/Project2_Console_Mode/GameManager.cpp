#include "GameManager.h"

Chess Board::board[10][9];

//File
//load file
bool File::Load(vector<string>& data) {  //XDD
	file.open(filename);
	if (!file) {
		cout << "File \"" + filename + "\" can't be opened.\n";
		return false;
	}
	else {
		cout << "File is loading...\n";
		Sleep(2000);

		string temp;
		for (; getline(file, temp);) {
			data.push_back(temp);
		}
		return true;
	}
}
//divide input. ex: Player: 1, Action: Cannon (x1, y1) -> (x2, y2)
void File::Input(string& data, int& color, string& character, int& x1, int& y1, int& x2, int& y2) {
	gotoxy(30, 20); cout << "Error:                                                  ";
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
	if (x1 == -1 || x2 == -1 || y1 == -1 || y2 == -1 || color == -1 || character == "") {
		throw "Wrong input format.";
	}
}
//output to a file
void File::Output() {
	fstream out(filename, ios::out | ios::trunc);
	for (int i = 0; i < gameRecord.size(); i++)
		out << gameRecord[i] << '\n';
	out.close();
}

//====================================================================================================

//Board

Board::Board() {
	initialization();
}

void Board::initialization() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			board[i][j] = Null(j, i);
		}
	}

	board[0][0] = Chariot(0, 0, BLACK_CHARIOT); board[0][8] = Chariot(8, 0, BLACK_CHARIOT);
	board[9][0] = Chariot(0, 9, RED_CHARIOT);   board[9][8] = Chariot(8, 9, RED_CHARIOT);
	board[0][1] = Horse(1, 0, BLACK_HORSE); board[0][7] = Horse(7, 0, BLACK_HORSE);
	board[9][1] = Horse(1, 9, RED_HORSE);   board[9][7] = Horse(7, 9, RED_HORSE);
	board[0][2] = Elephant(2, 0, BLACK_ELEPHANT); board[0][6] = Elephant(6, 0, BLACK_ELEPHANT);
	board[9][2] = Elephant(2, 9, RED_ELEPHANT);	  board[9][6] = Elephant(6, 9, RED_ELEPHANT);
	board[0][3] = Advisor(3, 0, BLACK_ADVISOR); board[0][5] = Advisor(5, 0, BLACK_ADVISOR);
	board[9][3] = Advisor(3, 9, RED_ADVISOR);   board[9][5] = Advisor(5, 9, RED_ADVISOR);
	board[0][4] = General(4, 0, BLACK_GENERAL); board[9][4] = General(4, 9, RED_GENERAL);
	board[2][1] = Cannon(1, 2, BLACK_CANNON); board[2][7] = Cannon(7, 2, BLACK_CANNON);
	board[7][1] = Cannon(1, 7, RED_CANNON);   board[7][7] = Cannon(7, 7, RED_CANNON);
	board[3][0] = Soldier(0, 3, BLACK_SOLDIER); board[3][2] = Soldier(2, 3, BLACK_SOLDIER); board[3][4] = Soldier(4, 3, BLACK_SOLDIER);
	board[3][6] = Soldier(6, 3, BLACK_SOLDIER); board[3][8] = Soldier(8, 3, BLACK_SOLDIER);
	board[6][0] = Soldier(0, 6, RED_SOLDIER); board[6][2] = Soldier(2, 6, RED_SOLDIER); board[6][4] = Soldier(4, 6, RED_SOLDIER);
	board[6][6] = Soldier(6, 6, RED_SOLDIER); board[6][8] = Soldier(8, 6, RED_SOLDIER);
	return;
}
//check input player, chess_type is correspnding to the chess on the board[y][x]
bool Board::checkChess(Chess chess, int& color, string& character) {
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
	return false;
}
//to move choosed chess 
void Board::moveChess(File& file, int& color, string& character, int& x1, int& y1, int& x2, int& y2) {
	if (checkChess(getChess(x1, y1), color, character)) {
		//show moveable path
		//cin >> x2 >> y2

		bool general_death = false;
		if (board[y2][x2].chess_type % 10 == GENERAL) general_death = true;
		board[y2][x2] = board[y1][x1];  //move
		board[y1][x1] = Null(x1, y1);


		string str = "Player: " + to_string(color) + ", Action: " + character +
			" (" + to_string(x1) + ", " + to_string(y1) + ") -> (" + to_string(x2) + ", " + to_string(y2) + ")     ";
		file.gameRecord.push_back(str);
		if (general_death) {
			if (color == BLACK) file.gameRecord.push_back("Black Win");
			else file.gameRecord.push_back("Red Win");
		}
		gotoxy(20, 3);
		cout << str;
	}
	else throw "Move chess fail, for wrong color or chess";
}

void Board::showBoard() {
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

//====================================================================================================

//GameManager
//no use
int GameManager::checkChess(int x, int y) {
	vector<Pos> cango;
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
	return 0;
}