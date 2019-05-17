#include <string>
#include <iostream>
#include <iomanip>
#include<windows.h>
using namespace std;

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

