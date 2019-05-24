#ifndef _DRAW_
#define _DRAW_
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <windows.h>
#include <utility>
#include "Color.h"
#include "Cursor.h"
using namespace std;
class Game;
class Draw
{

public:
	
	static const string rowLine;
	static const string verticalBar;
	static const string infoBlock[];
	static const string dialogueBox[10];
	static const string boundary[34];
	static const Cursor cursor;
	static const int FIRST;
	static const int SECOND;


	static void showplayerlist(vector<int>);
	static void showcurrentplayer();
	static void drawDialogueBox(string title, pair<string, string> chooseName, bool status);
	static void drawDialogueBox(string title, string content = "");
	static void drawMap();
};
#endif // !_DRAW_