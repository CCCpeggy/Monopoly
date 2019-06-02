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
using namespace std;
#pragma endregion
#pragma region define
#define LAND 0
#define CHANCE 1
#define FATE 2
#define ALL -1
#define LOADFILE "basemap2.txt"
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
	bool saveFile();
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
	bool endMenu();
	void showMap();
	void showAllPlayerStatus(); //玩家狀態
	void showMapContent();
	void showBlockContent(int);
	bool showPlayStatus();
	void showActionMenu();
	void showGameStatus();
	bool playerBroken();
	static int getDice(int);
	void checkMoney();
	bool checkGameStatus();
	void showWinner();
	bool backHome();
public:
	Game(string = LOADFILE, bool = true);
	static int showNumberDialog(string, int = 0, int = 10000, int = -10000, int = 1, string unit = "");
	static void cleanCenter();
	static bool showDialog(string, pair<string, string>, bool = Draw::FIRST);
	static void showDialog(string = "", string = "");
	static void showDice(pair<int, int>);
	static int showMenu(string, vector<string>, int = 0, void(*function)(string) = nullptr);
	static int keyBoard();
	BaseBlock* showChoosingMapMode(string);
	Player* getPlayer();
	void getMoneyFromEveryPlayer(int);
	void giveMoneyToEveryPlayer(int);
	void drawStockInfo(int);
	pair<vector<string>, std::map<int, bool(Game::*)(void)> > getAction(int = 所有動作);
	~Game();
};

#endif