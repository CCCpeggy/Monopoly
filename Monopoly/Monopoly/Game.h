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
#include <map>
#pragma endregion
#pragma region define
#define LAND 0
#define CHANCE 1
#define FATE 2
#define ALL -1
#define LOADFILE "init2.txt"
#define ¯}²£ false
#define ´I¯Î true
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
	void putTool();
	void saveMoney();
	void borrowMoney();
	void returnMoney();
	void doStock();
	pair<vector<string>, std::map<int, void(Game::*)(void)> > getAction();
	void rollDice();
	void overGame(string = "");
	void showMap();
	void showAllPlayerStatus(); //ª±®aª¬ºA
	void showMapContent();
	void showPlayStatus();
	void showActionMenu();
	int showNumberDialog(string, int = 0, int = 10000, int = -10000, int = 1, string unit = "");
	static void cleanCenter();
	static bool showDialog(string, pair<string, string>, bool = Draw::FIRST);
	static void showDialog(string, string);
	static void showDice(pair<int, int>);
	static int showMenu(string, vector<string>, int = 0);
	static int keyBoard();
};

#endif