#include "Color.h"
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

void Color::setTextColor(int color)
{
	SetConsoleTextAttribute(handleOutput, color);
}