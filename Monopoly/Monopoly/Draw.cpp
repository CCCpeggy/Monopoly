#include "Draw.h"

extern HANDLE handleOutput;

#pragma region Color
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

#pragma endregion

#pragma region Draw
const string Draw::rowLine = "�D�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�D";
const string Draw::verticalBar = "�U";
const string Draw::dialogueBox[10] = { "���X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X��" ,
																				  "���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��" ,
																				  "���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��" ,
																				  "���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��" ,
																				  "���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��",
																				  "���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��",
																				  "���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��",
																				  "���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��",
																				  "���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��",
																				  "���X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X��" };
const string Draw::infoBlock[] = {
										   "���X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X��",
										   "���@�@�@�@�U�@�@�@�@�U�@�@�@�@�U�@�@�@�@�U�@�@�@�@��",
										   "���X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X��" ,
										   "���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��" ,
										   "���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��" ,
										   "���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��" ,
										   "���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��",
										   "���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��",
										   "���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��",
										   "���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��",
										   "���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��",
										   "���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��",
										   "���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��",
										   "���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��",
										   "���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��",
										   "���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��",
										   "���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��",
											"���X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X��"
};

#define DIALOG_CONTENT_LEN 46
void Draw::drawDialogueBox(string title, int status)
{
	Cursor cursor(15, 10);
	for (int i = 0; i <= 9; i++)
	{
		cursor.inputPos(0, i);
		cout << dialogueBox[i] << endl;
	}
	cursor.set(17, 12);

	cursor.inputPos(computeCenter(DIALOG_CONTENT_LEN, title.length()));
	cout << title;

	if (status == 0)
	{
		cursor.inputPos(10, 5);
		Color::setTextColor(Color::TAG_CHOOSE_COLOR);
		cout << "�O";

		cursor.inputPos(33, 5);
		Color::setTextColor(Color::DEF_COLOR);
		cout << "�_";
	}
	else if (status == 1)
	{
		cursor.inputPos(10, 5);
		Color::setTextColor(Color::DEF_COLOR);
		cout << "�O";
		cursor.inputPos(33, 5);
		Color::setTextColor(Color::TAG_CHOOSE_COLOR);
		cout << "�_";
	}
	else if (status == 2)
	{
		cursor.inputPos(10, 5);
		Color::setTextColor(Color::TAG_CHOOSE_COLOR);
		cout << "�R";
		cursor.inputPos(33, 5);
		Color::setTextColor(Color::DEF_COLOR);
		cout << "��";
	}
	else if (status == -2)
	{
		cursor.inputPos(10, 5);
		Color::setTextColor(Color::DEF_COLOR);
		cout << "�R";
		cursor.inputPos(33, 5);
		Color::setTextColor(Color::TAG_CHOOSE_COLOR);
		cout << "��";
	}
	Color::setTextColor(Color::DEF_COLOR);
}

void Draw::drawDialogueBox(string title, string content) {
	Cursor cursor(15, 10);
	for (int i = 0; i <= 9; i++)
	{
		cursor.inputPos(0, i);
		cout << dialogueBox[i] << endl;
	}

	cursor.set(17, 12);
	cursor.inputPos(computeCenter(DIALOG_CONTENT_LEN, title.length()));
	cout << title;

	for (int i = 0; i < 3; i++) {
		int startPos = computeCenter(DIALOG_CONTENT_LEN, content.length(), i);
		cursor.inputPos(startPos, 3 + i);
		if (startPos != 0) {
			cout << content.substr(i * DIALOG_CONTENT_LEN);
			break;
		}
		cout << content.substr(i * DIALOG_CONTENT_LEN, DIALOG_CONTENT_LEN);
	}
	
	Color::setTextColor(Color::DEF_COLOR);
}

int Draw::computeCenter(int containerLength, int stringLength, int Line)
{
	stringLength -= containerLength * Line;
	if (stringLength > containerLength) return 0;
	return (containerLength - stringLength) / 2;
}

void Draw::showplayerlist(vector<int> dollarinfo)
{
	Cursor cursor(0, 34);
	int line = 0;
	cursor.inputPos(0, line++);
	cout << rowLine;
	cursor.inputPos(0, line++);
	cout << verticalBar << "�@���a�@";
	SetConsoleTextAttribute(handleOutput, Color::B_BLUE);
	cout << left << setw(16) << "1";
	SetConsoleTextAttribute(handleOutput, Color::DEF_COLOR);
	cout << verticalBar;
	SetConsoleTextAttribute(handleOutput, Color::B_GREEN);
	cout << left << setw(16) << "2";
	SetConsoleTextAttribute(handleOutput, Color::DEF_COLOR);
	cout << verticalBar;
	SetConsoleTextAttribute(handleOutput, Color::B_CYAN);
	cout << left << setw(16) << "3";
	SetConsoleTextAttribute(handleOutput, Color::DEF_COLOR);
	cout << verticalBar;
	SetConsoleTextAttribute(handleOutput, Color::B_RED);
	cout << left << setw(16) << "4";
	SetConsoleTextAttribute(handleOutput, Color::DEF_COLOR);
	cout << verticalBar << endl << verticalBar << "�@�{���@";
	cout << " " << left << setw(15) << dollarinfo[0] << verticalBar;
	cout << " " << left << setw(15) << dollarinfo[3] << verticalBar;
	cout << " " << left << setw(15) << dollarinfo[6] << verticalBar;
	cout << " " << left << setw(15) << dollarinfo[9] << verticalBar;
	cout << endl << verticalBar << "�@�ɴڡ@";
	cout << " " << left << setw(15) << dollarinfo[1] << verticalBar;
	cout << " " << left << setw(15) << dollarinfo[4] << verticalBar;
	cout << " " << left << setw(15) << dollarinfo[7] << verticalBar;
	cout << " " << left << setw(15) << dollarinfo[10] << verticalBar;
	cout << endl << verticalBar << "�@�s�ڡ@";
	cout << " " << left << setw(15) << dollarinfo[2] << verticalBar;
	cout << " " << left << setw(15) << dollarinfo[5] << verticalBar;
	cout << " " << left << setw(15) << dollarinfo[8] << verticalBar;
	cout << " " << left << setw(15) << dollarinfo[11] << verticalBar;
	cout << endl << rowLine;
}

void Draw::showcurrentplayer() {
	Cursor cursor(0, 40);
	int line = 0;
	cursor.inputPos(0, line++);
	cout << verticalBar << "�ثe�C����" << setw(58) << " " << "��e�^�X��" << verticalBar;
	cursor.inputPos(0, line++);
	cout << verticalBar << " " << "1" << setw(75) << " " << "1" << verticalBar;
	cursor.inputPos(0, line++);
	cout << rowLine;
}


#pragma endregion

