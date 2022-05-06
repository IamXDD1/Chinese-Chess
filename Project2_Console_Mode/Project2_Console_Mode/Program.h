#pragma once
#include <fstream>
#include "Clock.h"
#include "GameManager.h"
#include "Clock.h"

class Program {
public:
	void Run() {
		menu();
		switch (chooseOption())
		{
		case 1: startGame(); break;
		case 2: loadFile();  break;
		case 3: leaveGame(); return;
		}
	}
	void menu();
	int chooseOption();
	void clearScreen();
	void startGame();
	void loadFile();
	void leaveGame();
};