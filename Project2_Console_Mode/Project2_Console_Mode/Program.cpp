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
	GameManager GM;
	File file;
	string filename;

	cin.get();

	cout << "Please input a file name to output : ";
	getline(cin, filename);
	file.setFilename(filename + ".txt");

	clearScreen();
	GM.gameBoard.showBoard();

	//keep playing
	GameRun(GM, file);
	file.Output();

	playagain();
}

void Program::loadFile()
{
	GameManager GM;
	vector<string> data;
	File file;
	string filename;

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
		if (file.gameRecord.size() > 0)
			if (file.gameRecord[file.gameRecord.size() - 1] == "Black Win"
				|| file.gameRecord[file.gameRecord.size() - 1] == "Red Win") {
				Sleep(2000);
				clearScreen();
				cout << "Game Over! " << file.gameRecord[file.gameRecord.size() - 1] << '\n';
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
		GM.gameBoard.moveChess(file, color, charactor, x1, y1, x2, y2);
		GM.gameBoard.showBoard();
	}

	//keep playing
	if (keep_playing) {
		gotoxy(0, 10);
		cout << "Keep playing from here!\n";
		cin.get();
		GameRun(GM, file);
	}
	file.Output();

	playagain();
}

void Program::leaveGame()
{
	return;
}

void Program::GameRun(GameManager& GM, File& file)
{
	for (; true;) {
		try {
			//Game keep run
			string cmd;
			gotoxy(0, 11);
			cout << "Input command : ";
			getline(cin, cmd);
			if (cin.eof()) break;

			int x1, x2, y1, y2, color;
			string charactor;
			file.Input(cmd, color, charactor, x1, y1, x2, y2);
			GM.gameBoard.moveChess(file, color, charactor, x1, y1, x2, y2);
			GM.gameBoard.showBoard();

			if (file.gameRecord[file.gameRecord.size() - 1] == "Black Win"
				|| file.gameRecord[file.gameRecord.size() - 1] == "Red Win") {
				Sleep(2000);
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
		else {
			cout << "Wrong command. Please input again. (Y/N) : ";
		}
	}
}