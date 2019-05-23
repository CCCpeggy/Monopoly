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
const string DialogueBox::dialogueBox[10] = { "■———————————————————————■" ,
																				  "∥　　　　　　　　　　　　　　　　　　　　　　　∥" ,
																				  "∥　　　　　　　　　　　　　　　　　　　　　　　∥" ,
																				  "∥　　　　　　　　　　　　　　　　　　　　　　　∥" ,
																				  "∥　　　　　　　　　　　　　　　　　　　　　　　∥",
																				  "∥　　　　　　　　　　　　　　　　　　　　　　　∥",
																				  "∥　　　　　　　　　　　　　　　　　　　　　　　∥",
																				  "∥　　　　　　　　　　　　　　　　　　　　　　　∥",
																				  "∥　　　　　　　　　　　　　　　　　　　　　　　∥",
																				  "■———————————————————————■" };
Grid::Grid()
{
	rowLine[0] = "——————————————————————————————————————";
	rowLine[1] = "｜————————————————————————————————————｜";
}


void Grid::showplayerlist(int player1dollar, int player2dollar, int player3dollar, int player4dollar)
{
	cout << verticalBar << "　玩家　" << verticalBar;
	SetConsoleTextAttribute(handleSTDOutput, color.B_BLUE);
	cout << left << setw(14) << "1";
	SetConsoleTextAttribute(handleSTDOutput, color.DEF_COLOR);
	cout << verticalBar;
	SetConsoleTextAttribute(handleSTDOutput, color.B_GREEN);
	cout << left << setw(14) << "2";
	SetConsoleTextAttribute(handleSTDOutput, color.DEF_COLOR);
	cout << verticalBar;
	SetConsoleTextAttribute(handleSTDOutput, color.B_CYAN);
	cout << left << setw(14) << "3";
	SetConsoleTextAttribute(handleSTDOutput, color.DEF_COLOR);
	cout << verticalBar;
	SetConsoleTextAttribute(handleSTDOutput, color.B_RED);
	cout << left << setw(14) << "4";
	SetConsoleTextAttribute(handleSTDOutput, color.DEF_COLOR);
	cout << verticalBar << endl << verticalBar << "　現金　" << verticalBar;
	cout << " " << left << setw(13) << player1dollar << verticalBar;
	cout << " " << left << setw(13) << player2dollar << verticalBar;
	cout << " " << left << setw(13) << player3dollar << verticalBar;
	cout << " " << left << setw(13) << player4dollar << verticalBar;
	cout << endl << verticalBar << "　借款　" << verticalBar;
	cout << " " << left << setw(13) << player1dollar << verticalBar;
	cout << " " << left << setw(13) << player2dollar << verticalBar;
	cout << " " << left << setw(13) << player3dollar << verticalBar;
	cout << " " << left << setw(13) << player4dollar << verticalBar;
	cout << endl << verticalBar << "　存款　" << verticalBar;
	cout << " " << left << setw(13) << player1dollar << verticalBar;
	cout << " " << left << setw(13) << player2dollar << verticalBar;
	cout << " " << left << setw(13) << player3dollar << verticalBar;
	cout << " " << left << setw(13) << player4dollar << verticalBar;
	cout << endl << rowLine[1] << endl;
}

void Grid::showcurrentplayer() {
	cout << verticalBar << "目前遊戲者" << setw(52) << " " << "當前回合數" << verticalBar << endl;
	cout << verticalBar << " " << "1" << setw(69) << " " << "1" << verticalBar << endl;

	cout << rowLine[1];
}

DialogueBox::DialogueBox()
{
	int k = 0;
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 10; i <= 19; i++)
	{
		COORD pos;
		pos.X = 15;
		pos.Y = i;
		SetConsoleCursorPosition(hOut, pos);
		cout << DialogueBox::dialogueBox[k] << endl;
		k++;
	}
}