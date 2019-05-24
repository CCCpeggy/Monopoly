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