#include "Draw.h"

const unsigned int Color::B_BLUE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE;
const unsigned int Color::B_GREEN = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_GREEN;
const unsigned int Color::B_CYAN = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN;
const unsigned int Color::B_RED = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED;
const unsigned int Color::F_BLUE = FOREGROUND_BLUE;
const unsigned int Color::F_GREEN = FOREGROUND_GREEN;
const unsigned int Color::F_CYAN = FOREGROUND_BLUE | FOREGROUND_GREEN;
const unsigned int Color::F_RED = FOREGROUND_RED;
const unsigned int Color::F_WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
const unsigned int Color::DEF_COLOR = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
const unsigned int Color::TAG_CHOOSE_COLOR = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
const unsigned int Color::B_PLAYER_COLOR[4] = { B_BLUE, B_GREEN, B_CYAN, B_RED };
const unsigned int Color::F_PLAYER_COLOR[4] = { F_BLUE, F_GREEN, F_CYAN, F_RED };

Grid::Grid()
{
	rowLine[0] = "—————————————————————————————————";
	rowLine[1] = "｜———————————————————————————————｜";
}


void Grid::showplayerlist()
{
	cout << verticalBar;
	whiteonBlue();
	cout << left << setw(14) << "1";
	defaultcolor();
	cout << verticalBar;
	whiteonGreen();
	cout << left << setw(14) << "2";
	defaultcolor();
	cout << verticalBar;
	whiteonCyan();
	cout << left << setw(14) << "3";
	defaultcolor();
	cout << verticalBar;
	whiteonRed();
	cout << left << setw(14) << "4";
	defaultcolor();
	cout << verticalBar << endl << verticalBar;
	//tmpdollar之後會換成玩家的錢
	cout << " " << left << setw(13) << tmpdollar << verticalBar;
	cout << " " << left << setw(13) << tmpdollar << verticalBar;
	cout << " " << left << setw(13) << tmpdollar << verticalBar;
	cout << " " << left << setw(13) << tmpdollar << verticalBar;
	cout << endl << rowLine[1] << endl;
}

void Grid::showcurrentplayer() {
	cout << verticalBar << "目前遊戲者" << setw(42) << " " << "當前回合數" << verticalBar << endl;
	cout << verticalBar << " " << "1" << setw(59) << " " << "1" << verticalBar << endl;

	cout << rowLine[1];
}