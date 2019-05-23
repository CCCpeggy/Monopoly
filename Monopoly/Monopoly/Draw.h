#ifndef _DRAW_
#define _DRAW_
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <windows.h>
#include "Cursor.h"
using namespace std;

class Color {
	public :
	static const unsigned int B_BLUE;
	static const unsigned int B_GREEN;
	static const unsigned int B_CYAN;
	static const unsigned int B_RED;
	static const unsigned int F_BLUE;
	static const unsigned int F_GREEN;
	static const unsigned int F_CYAN;
	static const unsigned int F_RED;
	static const unsigned int F_WHITE;
	static const unsigned int DEF_COLOR;
	static const unsigned int TAG_CHOOSE_COLOR;
	static const unsigned int B_PLAYER_COLOR[4]; //¦a¦W
	static const unsigned int F_PLAYER_COLOR[4]; //ª±®a
	static void setTextColor(int);
};

class Draw
{

public:
	
	static const string rowLine;
	static const string verticalBar;
	static const string infoBlock[];
	static const string dialogueBox[10];

	static void showplayerlist(vector<int>);
	static void showcurrentplayer();
	static void drawDialogueBox(string title, int status);
	static void drawDialogueBox(string title, string content = "");
	static int computeCenter(int containerLength, int stringLength, int Line = 0);
};
#endif // !_DRAW_