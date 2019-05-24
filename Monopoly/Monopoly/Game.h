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
#define �}�� false
#define �I�� true
#pragma endregion
class Game
{
private:
	//Cursor informCursor;
	Map map;
	vector<Stock> stock;
	vector<Player> player;
	int playerIndex;
	int round;
public:
	Game(string = LOADFILE);
	void loadFile(string);
	void stockFluctuate();
	bool noMoney(); 
	void sellEstate();
	void showMap();
	void showAllPlayerStatus(); //���a���A
	void showPlayerInfo();
	void showMapContent();
	void showPlayStatus(int);
	void showActionMenu();
	static void cleanCenter();
	static bool showDialog(string, pair<string, string>, bool = Draw::FIRST);
	static void showDialog(string, string);
	static void showDice(pair<int, int>);
	static int showMenu(string, vector<string>, int = 0);
	static int keyBoard();
};

#endif