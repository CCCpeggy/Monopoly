#ifndef _COLOR_
#define _COLOR_
#include <windows.h>
extern HANDLE handleOutput;

class Color {
public:
	static const unsigned int B_PURPLE;
	static const unsigned int B_GREEN;
	static const unsigned int B_CYAN;
	static const unsigned int B_RED;
	static const unsigned int F_PURPLE;
	static const unsigned int F_GREEN;
	static const unsigned int F_CYAN;
	static const unsigned int F_RED;
	static const unsigned int F_WHITE;
	static const unsigned int DEF_COLOR;
	static const unsigned int TAG_CHOOSE_COLOR;
	static const unsigned int B_WHITE_F_RED;
	static const unsigned int B_WHITE_F_GREEN;
	static const unsigned int B_PLAYER_COLOR[4]; //¦a¦W
	static const unsigned int F_PLAYER_COLOR[4]; //ª±®a
	static void setTextColor(int);
};
#endif // !_COLOR_