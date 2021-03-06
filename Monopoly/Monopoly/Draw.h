#ifndef _DRAW_
#define _DRAW_
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <windows.h>
#include <utility>
#include <sstream>
#include "Color.h"
#include "Cursor.h"
using namespace std;
class Game;
class Draw
{

public:
	
	static const string rowLine;
	static const string verticalBar;
	static const string infoBlock[18];
	static const string dialogueBox[10];
	static const string boundary[5];
	static const Cursor cursor;
	static Cursor playerStatusCursor;
	static Cursor dialogCursor;
	static const string number[10];
	static const string playInfoTitle[5];
	static const string gameStatusFrame[10];
	static const string stockInfoBlock[18];
	static const string EstateBlockInfoBlock[18];
	static const string playerEstateInfoTitle[3];
	static const string playerStockInfoTitle[3];
	static const string playerItemTitle[2];
	static const string itemName[2];
	static const string stockInfoTitle[3];
	static const string stockTradeInfo[6];
	static const string diceone[5];
	static const string dicetwo[5];
	static const string dicethree[5];
	static const string dicefour[5];
	static const string dicefive[5];
	static const string dicesix[5];
	static const string houseLevelSymbol[4];
	static const int FIRST;
	static const int SECOND;

	static void drawDialogueBox(string title, pair<string, string> chooseName, bool status);
	static void drawDialogueBox(string title, string content = "");
	static void drawDialogueBox(string title, int num, string unit = "");
	static void drawMap(int = 7);
	static void drawDice(int dice1, int dice2);
	static void drawMenu(vector<string>, string, int);
	static void drawInfo(string, vector<string>, vector<vector<string> >, int, int = 1, int = 0, bool hasFrame = true);
	static void drawInfo(string, vector<string >, int = 0, bool hasFrame = true);
	static void drawPlayerInfoTitle(int);
	
	static void drawPlayerInfoFrame();
	static void drawStockInfoFrame();
	static void drawEstateBlockInfoFrame();
	static void drawGameStatusFrame();
	static void cleanCenter();
	static void cleanPlayerInfoContent();
};
#endif // !_DRAW_