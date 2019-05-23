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
void DialogueBox::drawDialogueBox(string title, int status, string context)
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
	COORD initPos;
	initPos.X = 17 + (47 - title.length()) / 2;
	initPos.Y = 12;
	COORD contextPos;
	contextPos.X = 17 + (47 - context.length()) / 2;
	contextPos.Y = 17;
	SetConsoleCursorPosition(hOut, initPos);
	cout << title;
	COORD choiceYPos;
	choiceYPos.X = 27;
	choiceYPos.Y = 17;
	COORD choiceNPos;
	choiceNPos.X = 50;
	choiceNPos.Y = 17;
	if (status == 0)
	{
		SetConsoleCursorPosition(hOut, choiceYPos);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::TAG_CHOOSE_COLOR);
		cout << "是";
		SetConsoleCursorPosition(hOut, choiceNPos);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::DEF_COLOR);
		cout << "否";
	}
	else if (status == 1)
	{
		SetConsoleCursorPosition(hOut, choiceYPos);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::DEF_COLOR);
		cout << "是";
		SetConsoleCursorPosition(hOut, choiceNPos);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::TAG_CHOOSE_COLOR);
		cout << "否";
	}
	else if (status == 2)
	{
		SetConsoleCursorPosition(hOut, choiceYPos);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::TAG_CHOOSE_COLOR);
		cout << "買";
		SetConsoleCursorPosition(hOut, choiceNPos);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::DEF_COLOR);
		cout << "賣";
	}
	else if (status == -2)
	{
		SetConsoleCursorPosition(hOut, choiceYPos);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::DEF_COLOR);
		cout << "買";
		SetConsoleCursorPosition(hOut, choiceNPos);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::TAG_CHOOSE_COLOR);
		cout << "賣";
	}
	else if (status == -1)
	{
		SetConsoleCursorPosition(hOut, contextPos);
		cout << context;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::DEF_COLOR);
}
Grid::Grid()
{
	
}


void Grid::showplayerlist(vector<int> dollarinfo)
{
	cout << rowLine << endl;
	cout << verticalBar << "　玩家　";
	SetConsoleTextAttribute(handleSTDOutput, color.B_BLUE);
	cout << left << setw(16) << "1";
	SetConsoleTextAttribute(handleSTDOutput, color.DEF_COLOR);
	cout << verticalBar;
	SetConsoleTextAttribute(handleSTDOutput, color.B_GREEN);
	cout << left << setw(16) << "2";
	SetConsoleTextAttribute(handleSTDOutput, color.DEF_COLOR);
	cout << verticalBar;
	SetConsoleTextAttribute(handleSTDOutput, color.B_CYAN);
	cout << left << setw(16) << "3";
	SetConsoleTextAttribute(handleSTDOutput, color.DEF_COLOR);
	cout << verticalBar;
	SetConsoleTextAttribute(handleSTDOutput, color.B_RED);
	cout << left << setw(16) << "4";
	SetConsoleTextAttribute(handleSTDOutput, color.DEF_COLOR);
	cout << verticalBar << endl << verticalBar << "　現金　" ;
	cout << " " << left << setw(15) << dollarinfo[0] << verticalBar;
	cout << " " << left << setw(15) << dollarinfo[3] << verticalBar;
	cout << " " << left << setw(15) << dollarinfo[6] << verticalBar;
	cout << " " << left << setw(15) << dollarinfo[9] << verticalBar;
	cout << endl << verticalBar << "　借款　" ;
	cout << " " << left << setw(15) << dollarinfo[1] << verticalBar;
	cout << " " << left << setw(15) << dollarinfo[4] << verticalBar;
	cout << " " << left << setw(15) << dollarinfo[7] << verticalBar;
	cout << " " << left << setw(15) << dollarinfo[10] << verticalBar;
	cout << endl << verticalBar << "　存款　";
	cout << " " << left << setw(15) << dollarinfo[2] << verticalBar;
	cout << " " << left << setw(15) << dollarinfo[5] << verticalBar;
	cout << " " << left << setw(15) << dollarinfo[8] << verticalBar;
	cout << " " << left << setw(15) << dollarinfo[11] << verticalBar;
	cout << endl << rowLine << endl;
}

void Grid::showcurrentplayer() {
	cout << verticalBar << "目前遊戲者" << setw(58) << " " << "當前回合數" << verticalBar << endl;
	cout << verticalBar << " " << "1" << setw(75) << " " << "1" << verticalBar << endl;

	cout << rowLine;
}
