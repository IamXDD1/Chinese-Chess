#include <iostream>
#include "Program.h"

using namespace std;

int main() {
	Program exe;
	exe.Run();
	//=============================================================================================================================
	//clock test
	/*
	GameClock GameTime;
	PlayerClock PlayerTime;
	int player = RED;
	while (true)
	{
		if (player == RED) player = BLACK;
		else if (player == BLACK) player = RED;
		string record = checkChess(player, GameTime, PlayerTime);  //-> include (moveable, move, checkmate)  and  time execute
	}*/
	//=============================================================================================================================
	//outline
	/*
	last turn/next turn   --->   use deque<string> to execute?
	{
		switch(chooseOption())
		{
			case 1: startGame(filename); break;
			case 2: loadFile();  break;
			case 3: leaveGame(); break;
		}
	}
	startGame(filename)
	{
		if(filename == "") {
			GameManager GM;
			GM.setEnvironment();  // --> file
			GM.GameRun()
			{
				GameClock GameTime;
				PlayerClock PlayerTime;
				while(true)
				{
					if(player == RED) player = BLACK;
					if(player == BLACK) player = RED;

					string record = checkChess(player, GameTime, PlayerTime);  //-> include (moveable, move, checkmate)  and  time execute

					writefile(record);

					if(endGame) { 
						savefile;

						Y -> startGame("");
						N -> back to ProgramRun.
					}
				}
			}
		}
	}

	string checkChess(int player, GameClock GameTime, PlayerClock PlayerTime)
	{
		time_t st = time(NULL);
		time_t base_time = 120;

		while(true)
		{
			time_t curr_time = time(NULL);
			GameTime.TotalTime = curr_time - GameTime.StartTime;

			if(player == BLACK){
				if (base_time != 0) {
					base_time = TIME_LIMIT - (curr_time - st);
				}
				else {
					PlayerTime.black_time += TIME_LIMIT - (curr_time - st);
				}
			}
			else if (player == RED) {
				if (base_time != 0) {
					base_time = TIME_LIMIT - (curr_time - st);
				}
				else {
					PlayerTime.red_time += TIME_LIMIT - (curr_time - st);
				}
			}
		}
	}
	*/
	return 0;
}