#include "Program.h"

void Program::menu()
{
	cout << "                                               " << '\n'
		<< "                                               " << '\n'
		<< "                                               " << '\n'
		<< "             please choose an option           " << '\n'
		<< "                1. start new game              " << '\n'
		<< "                2. load game                   " << '\n'
		<< "                3. leave game                  " << '\n'
		<< "                                               " << '\n'
		<< "                                               " << '\n'
		<< "                                               " << '\n';
}

void Program::clearScreen() {
	gotoxy(0, 0);
	for (int i = 0; i < 30; i++)
		cout << "                                                                                        \n";
	gotoxy(0, 0);
}

int Program::chooseOption()
{
	int number;
	cout << "Please choose an option : ";
	for (; cin >> number;) {
		if (number > 0 && number <= 3) return number;
		else cout << "wrong option! Please choose again.\nYour option : ";
	}
}
//new game
void Program::startGame()
{
	GameManager GM;
	File file;
	srand(time(NULL));
	string filename = "./game data/log_" + to_string(rand()) + ".txt";
	int round = 1;

	cin.get();

	file.setFilename(filename + ".txt");

	clearScreen();
	GM.gameBoard.showBoard();

	//keep playing
	GameRun(GM, file, round);
	file.Output();

	playagain();
}
//read file's input to move chess
void Program::loadFile()
{
	GameManager GM;
	vector<string> data;
	File file;
	string filename;
	int round = 1;

	cin.get();
	for (;;)
	{
		cout << "Please input a file name to load : ";
		getline(cin, filename);

		file.setFilename(filename + ".txt");
		if (file.Load(data)) break;
	}
	file.closeFile();

	clearScreen();
	GM.gameBoard.showBoard();

	//read file 
	bool keep_playing = true;
	for (int i = 0; i < data.size(); i++) {
		if (file.gameRecord.size() > 0) {
			if (file.gameRecord[file.gameRecord.size() - 1] == "Black Win"
				|| file.gameRecord[file.gameRecord.size() - 1] == "Red Win") {
				Sleep(1000);
				clearScreen();
				cout << "Game Over! " << file.gameRecord[file.gameRecord.size() - 1] << '\n';
				keep_playing = false;
				break;
			}
		}

		if (data[i] == "Red Win" || data[i] == "Black Win") {
			file.gameRecord.push_back(data[i]);
			Sleep(1000);
			clearScreen();
			cout << "Game Over! " << file.gameRecord[file.gameRecord.size() - 1] << " because ";
			if (data[i][0] == 'R') cout << "Black surrender." << '\n';
			else cout << "Red surrender." << '\n';
			keep_playing = false;
			break;
		}

		int choice;
		gotoxy(20, 0); cout << "1.any input to next turn (except 2).";
		gotoxy(20, 1); cout << "2.start from here.";
		gotoxy(20, 2); cout << "Input option : ";
		cin >> choice;
		if (choice == 2) break;

		int x1 = -1, x2 = -1, y1 = -1, y2 = -1, color = -1;
		string charactor;
		file.Input(data[i], color, charactor, x1, y1, x2, y2);
		color = (round % 2 == 1) ? RED : BLACK;
		GM.gameBoard.moveChess(file, x1, y1, x2, y2, true);
		GM.gameBoard.showBoard();
		round++;
	}

	//keep playing
	if (keep_playing) {
		gotoxy(0, 10);
		cout << "Keep playing from here!\n";
		cin.get();
		GameRun(GM, file, round);
	}
	file.Output();

	playagain();
}

void Program::leaveGame()
{
	return;
}
//input cmd to move chess
void Program::GameRun(GameManager& GM, File& file, int& round)
{
	GameClock GameTime;
	PlayerClock PlayerTime;
	for (; true;) {
		try {
			//timer(GameTime, PlayerTime, round);

			//Game keep run
			string charactor;
			gotoxy(0, 11);
			cout << "Input charactor (or input 'surrender'): ";
			//getline(cin, cmd);

			bool isCheckmate = false;
			int color = (round % 2 == 1) ? RED : BLACK;
			Board::load_all_chess_cango();

			cin >> charactor;
			if (cin.eof()) break;
			GM.gameBoard.load_all_chess_cango();
			GM.gameBoard.showallPath();
			int x1, x2, y1, y2;
			if (charactor != "surrender") {
				cout << "x1 = ";
				cin >> x1;
				cout << "y1 = ";
				cin >> y1;
				//file.Input(cmd, color, charactor, x1, y1, x2, y2);
				color = (round % 2 == 1) ? RED : BLACK;
				GM.gameBoard.moveChess(file, x1, y1, x2, y2);
				GM.gameBoard.showBoard();
				round++;
			}
			else {
				color = (round % 2 == 1) ? RED : BLACK;
				if (color == BLACK) file.gameRecord.push_back("Red Win");
				else file.gameRecord.push_back("Black Win");
			}

			int colorToPass;
			if (color == BLACK) colorToPass = RED;
			else if (color == RED) colorToPass = BLACK;
			Board::load_all_chess_cango();
			if (Board::ifMoveThenLose(isCheckmate, colorToPass))
			{
				if (color == BLACK) file.gameRecord.push_back("Red Win");
				else file.gameRecord.push_back("Black Win");
			}

			if (file.gameRecord[file.gameRecord.size() - 1] == "Black Win"
				|| file.gameRecord[file.gameRecord.size() - 1] == "Red Win") {
				Sleep(1000);
				clearScreen();
				cout << "Game Over! " << file.gameRecord[file.gameRecord.size() - 1] << '\n';
				break;
			}
		}
		catch (const char* error) {
			gotoxy(36, 20);
			cout << error << " Please input again.         \n";
		}
	}
}

void Program::playagain()
{
	cout << "Wanna start a new game? (Y/N) : ";
	for (;;)
	{
		char choice;
		cin >> choice;
		if (choice == 'Y') {
			clearScreen();
			startGame();
			return;
		}
		else if (choice == 'N') {
			clearScreen();
			Run();
			return;
		}
		else if (cin.eof()) break;
		else {
			cout << "Wrong command. Please input again. (Y/N) : ";
		}
	}
}