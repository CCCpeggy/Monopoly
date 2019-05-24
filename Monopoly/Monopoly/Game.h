#ifndef _GAME_
#define _GAME_
#pragma region include
#include "BaseBlock.h"
#include "Player.h"
#include "Map.h"
#include "EstateBlock.h"
#include "FateBlock.h"
#include "StartBlock.h"
#include "ChanceBlock.h"
#include "Stock.h""
#include "Draw.h"
#include "Cursor.h"
#include <vector>
#include <string>
#include <iomanip>
#include <windows.h>
#include <utility>
#include <fstream>
#include <sstream>
#pragma endregion
#pragma region define
#define LAND 0
#define CHANCE 1
#define FATE 2
#define ALL -1
#define LOADFILE "init2.txt"
#pragma endregion
class Game
{
private:
	Map map;
	vector<Stock> stock;
	vector<Player> player;
	int playerIndex;
	int round;
public:
	Game(string = LOADFILE);
	void loadFile(string);
	void showMap();
	void showAllPlayerStatus(); //ª±®aª¬ºA
	void showPlayerInfo();
	void showPlayerPosition(int = ALL);
	void showBlockContent();
	void showPlayStatus(int);
	void showActionMenu();
	void cleanPlayerPosition(int = ALL);
	void cleanCenter();
	bool showDialog(string, pair<string, string>, bool = Draw::FIRST);
	int keyBoard();
};

#endif