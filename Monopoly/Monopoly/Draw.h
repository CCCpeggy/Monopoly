#ifndef _DRAW_
#define _DRAW_
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include<windows.h>
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
	
};
class DialogueBox
{
public:
	static const string dialogueBox[10];
	DialogueBox();
};
class Grid
{

public:
	Grid();
	Color color;
	HANDLE handleSTDOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	string rowLine = "¡D¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡X¡D";
	string verticalBar = "¡U";

	void showplayerlist(vector<int>);
	void showcurrentplayer();
};
#endif // !_DRAW_