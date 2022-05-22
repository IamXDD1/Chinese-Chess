#include "GameManager.h"
using std::cout;

Chess Board::board[10][9];
vector<pair<Pos, vector<Pos>>> Board::all_chess_cango;

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
	return;
}
//output to a file
void File::Output() {
	fstream out(filename, ios::out | ios::trunc);
	for (size_t i = 0; i < gameRecord.size(); i++)
		out << gameRecord[i] << '\n';
	out.close();
}

//====================================================================================================

//Board

Board::Board() {
	initialization();
}

void Board::initialization() {
	for (size_t i = 0; i < 10; i++) {
		for (size_t j = 0; j < 9; j++) {
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
bool Board::checkChess(Chess chess) {
	int color = chess.chess_type / 10;
	string character = chessname(chess.chess_type % 10);
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
void Board::moveChess(File& file, int& x1, int& y1, int& x2, int& y2, bool loading) {
	load_all_chess_cango();
	Chess temp_chess = getChess(x1, y1);
	/*
	try
	{
		bool isCheckmate = false;
		temp_chess.ifMoveThenLose(isCheckmate);
	}
	catch(const char* error)
	{
		std::cout << error << endl;
	}
	*/
	if (checkChess(temp_chess)) { // input chess (x1, y1)
		bool isCheckmate = false;
		bool general_death = false;
		if (loading == false) {
			vector<Pos> cango;
			useChess(temp_chess, cango);  //load moveable path
			showPath(cango);

			for (;;)
			{
				gotoxy(0, 21);
				cout << "x2 = ";
				cin >> x2;
				cout << "y2 = ";
				cin >> y2;			//click point to move
				if ((x2 >= 0 && x2 <= 8) && (y2 >= 0 && y2 <= 9)) break;
				else "position is out of range. please input again!";
			}

			if (checkcango(x2, y2, cango)) {
				if (board[y2][x2].chess_type % 10 == GENERAL) general_death = true;
				//else if(board[y2][x2].chess_type != -1) GM.on_board.push_back(board[y2][x2]);
				board[y2][x2] = board[y1][x1];  //move
				board[y1][x1] = Null(x1, y1);
				board[y2][x2].pos.x = x2;
				board[y2][x2].pos.y = y2;
			}
			else {
				throw "can't go to x2 y2";
				return;
			}
		}
		else {
			if (board[y2][x2].chess_type % 10 == GENERAL) general_death = true;
			//else if(board[y2][x2].chess_type != -1) GM.on_board.push_back(board[y2][x2]);
			board[y2][x2] = board[y1][x1];  //move
			board[y1][x1] = Null(x1, y1);
			board[y2][x2].pos.x = x2;
			board[y2][x2].pos.y = y2;
		}


		string str = "Player: " + to_string(board[y2][x2].chess_type / 10) + ", Action: " + chessname(board[y2][x2].chess_type % 10) +
			" (" + to_string(x1) + ", " + to_string(y1) + ") -> (" + to_string(x2) + ", " + to_string(y2) + ")     ";
		file.gameRecord.push_back(str);
		if (general_death) {
			if (board[y2][x2].chess_type / 10 == BLACK) file.gameRecord.push_back("Black Win");
			else file.gameRecord.push_back("Red Win");
		}
		gotoxy(20, 3);
		cout << str;
	}
	else throw "Move chess fail, for wrong color or chess";
}

void Board::showPath(vector<Pos>& cango) {
	gotoxy(0, 20);
	cout << "                                                                                                ";
	gotoxy(0, 20);
	for (size_t i = 0; i < cango.size(); i++) {
		cout << '(' << cango[i].x << ',' << cango[i].y << ')' << ' ';
	}
	return;
}

void Board::showallPath() {
	gotoxy(0, 20);
	cout << "                                                                                                ";
	gotoxy(0, 20);
	for (auto it : all_chess_cango) {
		cout << '(' << it.first.x << ',' << it.first.y << ')' << " : ";
		for (auto cango : it.second) {
			cout << '(' << cango.x << ',' << cango.y << ')' << ' ';
		}
		cout << '\n';
	}
	return;
}

bool Board::checkcango(int& x2, int& y2, vector<Pos>& cango) {
	for (size_t i = 0; i < cango.size(); i++) {
		if (x2 == cango[i].x && y2 == cango[i].y) return true;
	}
	return false;
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
			default: cout << "  "; break;
			}
		}
		cout << endl;
	}
}

void Board::load_all_chess_cango()
{
	all_chess_cango.clear();
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 10; j++) {
			vector<Pos> cango;
			if (board[j][i].chess_type != NULL_CHESS) {
				Board::useChess(board[j][i], cango);
				all_chess_cango.push_back({ Pos(i,j), cango });
				/*
				cout << j << ',' << i << ' ';
				for (int x = 0; x < cango.size(); x++) cout << cango[x].x << ',' << cango[x].y << ' ';
				cout << '\n';
				*/
			}
		}
	}
}

string Board::chessname(int type)
{
	switch (type) {
	case GENERAL: return "General";
	case ADVISOR: return "Advisor";
	case ELEPHANT:return "Elephant";
	case CHARIOT: return "Chariot";
	case HORSE:	return "Horse";
	case CANNON:	return "Cannon";
	case SOLDIER:	return "Soldier";
	}
	return string();
}

void Board::useChess(Chess& temp_chess, vector<Pos>& cango) {
	int x = temp_chess.pos.x, y = temp_chess.pos.y;
	if (temp_chess.chess_type % 10 == GENERAL) {
		General general(x, y, temp_chess.chess_type);
		general.moveable(x, y, cango);
	}
	else if (temp_chess.chess_type % 10 == ADVISOR) {
		Advisor advisor(x, y, temp_chess.chess_type);
		advisor.moveable(x, y, cango);
	}
	else if (temp_chess.chess_type % 10 == ELEPHANT) {
		Elephant elephant(x, y, temp_chess.chess_type);
		elephant.moveable(x, y, cango);
	}
	else if (temp_chess.chess_type % 10 == CHARIOT) {
		Chariot chariot(x, y, temp_chess.chess_type);
		chariot.moveable(x, y, cango);
	}
	else if (temp_chess.chess_type % 10 == HORSE) {
		Horse horse(x, y, temp_chess.chess_type);
		horse.moveable(x, y, cango);
	}
	else if (temp_chess.chess_type % 10 == CANNON) {
		Cannon cannon(x, y, temp_chess.chess_type);
		cannon.moveable(x, y, cango);
	}
	else if (temp_chess.chess_type % 10 == SOLDIER) {
		Soldier soldier(x, y, temp_chess.chess_type);
		soldier.moveable(x, y, cango);
	}
}

bool Board::ifMoveThenLose(bool& isCheckmate, int color) //need opponent's all_chess_cango and all allys' Pos 
{
	vector<Pos> oppo_all_chess_cango; // for checking if checkmate
	vector<pair<Pos, vector<Pos>>> ally_all_chess_cango;
	Chess board_for_test[10][9];
	int general_type;
	Pos our_general_pos;
	vector<Pos> general_cango;

	// fill in board_for_test
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 9; x++)
		{
			board_for_test[y][x] = Board::getChess(x, y);
		}
	}

	bool generalCanMove = false;
	for (pair<Pos, vector<Pos>>& element_of_all_chess_cango : Board::all_chess_cango) // red and black
	{
		Chess chess_on_board = Board::getChess(element_of_all_chess_cango.first.x, 
			element_of_all_chess_cango.first.y);

		// fill in "oppo_all_chess_cango"
		if (chess_on_board.getColor() != color) // not my color ( enemy )
		{
			for (Pos& element : element_of_all_chess_cango.second)
			{
				// only fill in the place they can go which doesnt include their current place on the board
				oppo_all_chess_cango.push_back(element);
			}
		}
		if (chess_on_board.getColor() == color) // my color ( ally )
		{
			// fill in "all_able_to_move_ally_pos"
			if (chess_on_board.chess_type % 10 != 7 && element_of_all_chess_cango.second.size() != 0)
			{
				ally_all_chess_cango.push_back({ element_of_all_chess_cango.first, 
					element_of_all_chess_cango.second });
			}
			// my general ( can move )
			else if (chess_on_board.chess_type % 10 == 7)
			{
				if(element_of_all_chess_cango.second.size() != 0) generalCanMove = true;

				general_type = chess_on_board.chess_type;
				our_general_pos = element_of_all_chess_cango.first;
				for (auto& i : element_of_all_chess_cango.second) general_cango.push_back(i);
			}
		}
	}

	// whether general can escape by himself
	if (checkmate(our_general_pos, oppo_all_chess_cango, isCheckmate) && generalCanMove)
	{
		if (gereral_can_escape(board_for_test, our_general_pos, general_cango, ally_all_chess_cango, color))
		{
			return false;
		}
		// 無欠行
	}

	for (auto i : ally_all_chess_cango)
	{
		if (ifMoveThenLose_simu(board_for_test, i, color) == 1)
		{
			return false;
		}
	}

	return true; // 欠行
}

bool Board::gereral_can_escape(Chess board[][9], Pos general_pos, vector<Pos> general_cango,
	vector<pair<Pos, vector<Pos>>> ally_all_chess_cango, int color)
{
	board[general_pos.y][general_pos.x] = Null(general_pos.x, general_pos.y);
	// general can escape by himself ?
	for (auto& general_cango_element : general_cango)
	{
		// Change the board
		board[general_cango_element.y][general_cango_element.x] = General(general_cango_element.x,
			general_cango_element.y, 7 + (color * 10));

		// declare
		vector<Pos> oppo_all_chess_cango;
		vector<pair<Pos, vector<Pos>>> all_chess_cango_test;

		// fill in "all_chess_can_go"
		load_all_chess_cango_test(board, all_chess_cango_test);

		// fill in " oppo_all_chess_cango"
		for (auto& element_of_all_chess_cango : all_chess_cango_test)
		{
			Chess chess_on_board = board[element_of_all_chess_cango.first.y][element_of_all_chess_cango.first.x];

			if (chess_on_board.getColor() != color)
			{
				for (Pos& element : element_of_all_chess_cango.second)
				{
					oppo_all_chess_cango.push_back(element);
				}
			}
		}

		// check whether "oppo_all_chess_cango" overlap general's position on the current board
		bool overlap = false;
		for (auto& oppo_all_chess_cango_element : oppo_all_chess_cango)
		{
			if (oppo_all_chess_cango_element == general_cango_element) // overlap
			{
				overlap = true;
				break;
			}
		}

		board[general_cango_element.y][general_cango_element.x] = Null(general_cango_element.x,
			general_cango_element.y);

		if (!overlap)
		{
			board[general_pos.y][general_pos.x] = General(general_pos.x, general_pos.y, 7 + (color * 10));
			return true;
		}
	}

	board[general_pos.y][general_pos.x] = General(general_pos.x, general_pos.y, 7 + (color * 10));
	return false;
}

int Board::ifMoveThenLose_simu(Chess board[][9], pair<Pos, vector<Pos>> simu, int color)
{
	Chess current = board[simu.first.y][simu.first.x];
	board[simu.first.y][simu.first.x] = Null(simu.first.x, simu.first.y);

	for (auto& e : simu.second)
	{
		vector<pair<Pos, vector<Pos>>> all_chess_cango_test;
		Pos our_general_pos;
		vector<Pos> oppo_all_chess_cango;

		board[e.y][e.x] = current;

		load_all_chess_cango_test(board, all_chess_cango_test);

		//fill in "oppo_all_chess_cango"
		for (pair<Pos, vector<Pos>>& element_of_all_chess_cango : all_chess_cango_test)
		{
			Chess chess_on_board = board[element_of_all_chess_cango.first.y][element_of_all_chess_cango.first.x];

			if (chess_on_board.getColor() != color)
			{
				for (Pos& element : element_of_all_chess_cango.second)
				{
					oppo_all_chess_cango.push_back(element);
				}
			}
			else if ((chess_on_board.chess_type % 10 == 7))
			{
				our_general_pos.x = element_of_all_chess_cango.first.x; 
				our_general_pos.y = element_of_all_chess_cango.first.y;
			}
		}
		
		bool overlap = false;
		for (auto& i : oppo_all_chess_cango)
		{
			if (i == our_general_pos)
			{
				overlap = true;
				break;
			}
		}

		if (!overlap)
		{
			board[simu.first.y][simu.first.x] = current;
			return 1; // didnt overlap our general
		}

		board[e.y][e.x] = Null(e.x,e.y);
	}

	if (simu.first.x == 6 && simu.first.y == 0)
	{
		exit(1);
	}
	board[simu.first.y][simu.first.x] = current;
	return 0;
}

void Board::load_all_chess_cango_test(Chess boardT[][9], vector<pair<Pos, vector<Pos>>>& a)
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 10; j++) {
			vector<Pos> cango;
			if (boardT[j][i].chess_type != NULL_CHESS) {
				board_useChess(boardT[j][i], cango, boardT);
				a.push_back({ Pos(i,j), cango });
			}
		}
	}
}

//after move the 2nd movable() is required
bool Board::checkmate(Pos general_pos, vector<Pos>& oppo_all_chess_cango, bool& checkmate)
{
	// whether general can escape by himself
	for (auto& a : oppo_all_chess_cango)
	{
		if (a == general_pos) // checkmate 
		{
			checkmate = true;
			return true;
		}
	}
	return false;
}

void Board::board_useChess(Chess& temp_chess, vector<Pos>& cango, Chess board[][9])
{
	int x = temp_chess.pos.x, y = temp_chess.pos.y;
	if (temp_chess.chess_type % 10 == GENERAL) {
		General general(x, y, temp_chess.chess_type);
		general.board_moveable(x, y, cango, board);
	}
	else if (temp_chess.chess_type % 10 == ADVISOR) {
		Advisor advisor(x, y, temp_chess.chess_type);
		advisor.board_moveable(x, y, cango, board);
	}
	else if (temp_chess.chess_type % 10 == ELEPHANT) {
		Elephant elephant(x, y, temp_chess.chess_type);
		elephant.board_moveable(x, y, cango, board);
	}
	else if (temp_chess.chess_type % 10 == CHARIOT) {
		Chariot chariot(x, y, temp_chess.chess_type);
		chariot.board_moveable(x, y, cango, board);
	}
	else if (temp_chess.chess_type % 10 == HORSE) {
		Horse horse(x, y, temp_chess.chess_type);
		horse.board_moveable(x, y, cango, board);
	}
	else if (temp_chess.chess_type % 10 == CANNON) {
		Cannon cannon(x, y, temp_chess.chess_type);
		cannon.board_moveable(x, y, cango, board);
	}
	else if (temp_chess.chess_type % 10 == SOLDIER) {
		Soldier soldier(x, y, temp_chess.chess_type);
		soldier.board_moveable(x, y, cango, board);
	}
}
//====================================================================================================

//GameManager
//no use