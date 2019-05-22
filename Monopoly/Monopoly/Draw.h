#ifndef _DRAW_
#define _DRAW_
#include <string>
#include <iostream>
#include <iomanip>
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
class Grid
{

public:
	Grid();
	HANDLE handleSTDOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	string rowLine[2];
	string verticalBar = "¡U";
	string tmpdollar = "$50000";

	void showplayerlist();
	void showcurrentplayer();
	void defaultcolor() { SetConsoleTextAttribute(handleSTDOutput, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); };
	void whiteonBlue() { SetConsoleTextAttribute(handleSTDOutput, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE); };
	void whiteonGreen() { SetConsoleTextAttribute(handleSTDOutput, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_GREEN); };
	void whiteonCyan() { SetConsoleTextAttribute(handleSTDOutput, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN); };
	void whiteonRed() { SetConsoleTextAttribute(handleSTDOutput, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED); }
};

#endif // !_DRAW_