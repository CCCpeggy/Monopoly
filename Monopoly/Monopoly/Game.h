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
#include "BankBlock.h"
#include "Stock.h""
#include "Draw.h"
#include "Cursor.h"
#include "Item.h"
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
#define LOADFILE "init.txt"
#define 破產 false
#define 富翁 true
#define 所有動作 false
#define 銀行 true
#define 沒有選擇 -2147483647
#pragma endregion
class Game
{
private:
	//Cursor informCursor;
	Map map;
	vector<Stock*> stock;
	vector<Player> player;
	int playerIndex;
	int round;
	bool isOver;
	void loadFile(string);
	void saveFile(string);
	void stockFluctuate();
	bool noMoney();
	bool sellEstate();
	bool putItem();
	bool saveMoney();
	bool borrowMoney();
	bool returnMoney();
	bool withdrawMoney();
	bool doStock();
	bool rollDice();
	void overGame();
	bool endMenu();
	void showMap();
	void showAllPlayerStatus(); //玩家狀態
	void showMapContent();
	bool showPlayStatus();
	void showActionMenu();
	void showGameStatus();
	int showChoosingMapMode(string);
	bool playerBroken();
	static int getDice(int);
	void checkMoney();
	bool checkGameStatus();
	void showWinner();
public:
	Game(string = LOADFILE);
	static int showNumberDialog(string, int = 0, int = 10000, int = -10000, int = 1, string unit = "");
	static void cleanCenter();
	static bool showDialog(string, pair<string, string>, bool = Draw::FIRST);
	static void showDialog(string = "", string = "");
	static void showDice(pair<int, int>);
	static int showMenu(string, vector<string>, int = 0);
	static int keyBoard();
	Player* getPlayer();
	void getMoneyFromEveryPlayer(int);
	void giveMoneyToEveryPlayer(int);
	pair<vector<string>, std::map<int, bool(Game::*)(void)> > getAction(int = 所有動作);
	~Game();
};

#endif