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

void Program::startGame()
{
	clearScreen();
}

void Program::loadFile()
{
	GameManager GM;
	vector<string> data;
	File file;
	string filename;

	for (;;)
	{
		cout << "Please input a file name (end with .txt) : ";
		cin >> filename;

		file.setFilename(filename);
		if (file.Load(data)) break;
	}
	clearScreen();
	GM.gameBoard.showBoard();

	try {
		for (int i = 0; i < data.size(); i++) {
			if (data[i] == "Black Win") {
				file.gameRecord.push_back("Black Win");
				break;
			}
			else if (data[i] == "Red Win") {
				file.gameRecord.push_back("Red Win");
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
			GM.gameBoard.moveChess(file, color, charactor, x1, y1, x2, y2);
			GM.gameBoard.showBoard();
		}
		bool keep_playing = true;
		if (file.gameRecord[file.gameRecord.size() - 1] == "Black Win" 
			|| file.gameRecord[file.gameRecord.size() - 1] == "Red Win") {
			clearScreen();
			cout << "Game Over!";
			keep_playing = false;
		}
		if (keep_playing) {
			gotoxy(0, 11);
			cout << "Keep playing from here!";
		}
		for (; keep_playing;) {
			try {
				//Game keep run
				string cmd;
				getline(cin, cmd);

				int x1, x2, y1, y2, color;
				string charactor;
				file.Input(cmd, color, charactor, x1, y1, x2, y2);
				GM.gameBoard.moveChess(file, color, charactor, x1, y1, x2, y2);
				GM.gameBoard.showBoard();
			}
			catch (const char* error) {
				gotoxy(0, 11);
				cout << error << '\n';
			}

		}
	}
	catch (const char* error) {
		cout << error << '\n';
	}
}

void Program::leaveGame()
{
}
