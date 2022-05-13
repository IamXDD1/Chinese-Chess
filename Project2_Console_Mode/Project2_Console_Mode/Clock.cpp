#include "Clock.h"
//haven't bind to GM

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

void change_formate(int& min, int& sec, time_t total) {
	min = total / 60;
	sec = total % 60;
}

void printTime(GameClock& GameTime, PlayerClock& PlayerTime, time_t& base_time, int& player)
{
	gotoxy(40, 21);
	cout << "Total time : " << GameTime.TotalTime;

	if (player == RED) {
		gotoxy(40, 22);
		cout << "black use time : " << TIME_LIMIT << " + " << PlayerTime.black_time;
		gotoxy(40, 23);
		cout << "red use time : " << base_time << " + " << PlayerTime.red_time;
		gotoxy(40, 24);
		cout << " RED  TURN";
	}
	else {
		gotoxy(40, 22);
		cout << "black use time : " << base_time << " + " << PlayerTime.black_time;
		gotoxy(40, 23);
		cout << "red use time : " << TIME_LIMIT << " + " << PlayerTime.red_time;
		gotoxy(40, 24);
		cout << "BLACK TURN";
	}
}

string countingTime(int& player, GameClock& GameTime, PlayerClock& PlayerTime)
{
	time_t st = time(NULL);
	time_t base_time = TIME_LIMIT;
	time_t playertime = (player == BLACK) ? PlayerTime.black_time : PlayerTime.red_time;
	while (true)
	{
		time_t curr_time = time(NULL);
		GameTime.TotalTime = curr_time - GameTime.StartTime;
		int time = TIME_LIMIT - (curr_time - st);

		if (player == BLACK) {
			if (base_time > 0) {
				if (time <= 0) base_time = 0;
				else base_time = time;
			}
			else {
				PlayerTime.black_time = playertime + time; // ·|¦^¨ì1800
			}
			printTime(GameTime, PlayerTime, base_time, player);
		}
		else if (player == RED) {
			if (base_time > 0) {
				if (time <= 0) base_time = 0;
				else base_time = time;
			}
			else {
				PlayerTime.red_time = playertime + time;
			}
			printTime(GameTime, PlayerTime, base_time, player);
		}

		char a = getchar();
		//if (a == 's') break;
	}
	return "";
}