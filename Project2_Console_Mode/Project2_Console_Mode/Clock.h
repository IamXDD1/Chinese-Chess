#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>

#define BLACK 2
#define RED 1
#define TIME_LIMIT 10
#define PLAYER_BASE_TIME 1800

using namespace std;

void gotoxy(int x, int y);

class GameClock {
public:
	time_t StartTime; //minute : second
	time_t TotalTime;
	GameClock() { StartTime = time(NULL); TotalTime = 0; }
};

class PlayerClock {
public:
	int black_time;
	int red_time;
	PlayerClock() { 
		black_time = PLAYER_BASE_TIME;
		red_time = PLAYER_BASE_TIME;
	}
};