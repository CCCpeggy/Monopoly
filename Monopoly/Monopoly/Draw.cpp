#include "Draw.h"

extern HANDLE handleOutput;

const string Draw::rowLine = "．———————————————————————————————————————．";
const string Draw::verticalBar = "｜";
const string Draw::dialogueBox[10] = { "■———————————————————————■" ,
										"∥　　　　　　　　　　　　　　　　　　　　　　　∥" ,
										"∥　　　　　　　　　　　　　　　　　　　　　　　∥" ,
										"∥　　　　　　　　　　　　　　　　　　　　　　　∥" ,
										"∥　　　　　　　　　　　　　　　　　　　　　　　∥",
										"∥　　　　　　　　　　　　　　　　　　　　　　　∥",
										"∥　　　　　　　　　　　　　　　　　　　　　　　∥",
										"∥　　　　　　　　　　　　　　　　　　　　　　　∥",
										"∥　　　　　　　　　　　　　　　　　　　　　　　∥",
										"■———————————————————————■" };
const string Draw::infoBlock[] = {
										   "■————————————————————————■",
										   "∥　　　　｜　　　　｜　　　　｜　　　　｜　　　　∥",
										   "∥————————————————————————∥" ,
										   "∥　　　　　　　　　　　　　　　　　　　　　　　　∥" ,
										   "∥　　　　　　　　　　　　　　　　　　　　　　　　∥" ,
										   "∥　　　　　　　　　　　　　　　　　　　　　　　　∥" ,
										   "∥　　　　　　　　　　　　　　　　　　　　　　　　∥",
										   "∥　　　　　　　　　　　　　　　　　　　　　　　　∥",
										   "∥　　　　　　　　　　　　　　　　　　　　　　　　∥",
										   "∥　　　　　　　　　　　　　　　　　　　　　　　　∥",
										   "∥　　　　　　　　　　　　　　　　　　　　　　　　∥",
										   "∥　　　　　　　　　　　　　　　　　　　　　　　　∥",
										   "∥　　　　　　　　　　　　　　　　　　　　　　　　∥",
										   "∥　　　　　　　　　　　　　　　　　　　　　　　　∥",
										   "∥　　　　　　　　　　　　　　　　　　　　　　　　∥",
										   "∥　　　　　　　　　　　　　　　　　　　　　　　　∥",
										   "∥　　　　　　　　　　　　　　　　　　　　　　　　∥",
											"■————————————————————————■"
};

#define DIALOG_CONTENT_LEN 46
void Draw::drawDialogueBox(string title, int status)
{
	Cursor cursor(15, 10);
	for (int i = 0; i <= 9; i++)
	{
		cursor << dialogueBox[i];
		cursor.nextLine();
	}

	cursor.add(2,2);
	cursor << pair<string, int>(title, DIALOG_CONTENT_LEN);

	cursor.add(10, 5, 23);
	if (status == 0)
	{
		cursor << Color::TAG_CHOOSE_COLOR << "是";
		cursor.nextPos();
		cursor << Color::DEF_COLOR << "否";
	}
	else if (status == 1)
	{
		cursor << Color::DEF_COLOR << "是";
		cursor.nextPos();
		cursor << Color::TAG_CHOOSE_COLOR << "否";
	}
	else if (status == 2)
	{
		cursor << Color::TAG_CHOOSE_COLOR << "買";
		cursor.nextPos();
		cursor << Color::DEF_COLOR << "賣";
	}
	else if (status == -2)
	{
		cursor << Color::DEF_COLOR << "買"; 
		cursor.nextPos();
		cursor << Color::TAG_CHOOSE_COLOR << "賣";
	}
}

void Draw::drawDialogueBox(string title, string content) {
	Cursor cursor(15, 10);
	for (int i = 0; i <= 9; i++)
	{
		cursor << dialogueBox[i];
		cursor.nextLine();
	}

	cursor.add(2, 2);
	cursor << pair<string, int>(title, DIALOG_CONTENT_LEN);

	cursor.nextLine().nextLine().nextLine();
	for (int i = 0; i < 3; i++) {
		if ((DIALOG_CONTENT_LEN * (i+1)) >= content.length()) {
			cursor << pair<string, int>(content.substr(i * DIALOG_CONTENT_LEN), DIALOG_CONTENT_LEN);
			break;
		}
		cursor << content.substr(i * DIALOG_CONTENT_LEN, DIALOG_CONTENT_LEN);
		cursor.nextLine();
	}
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
	cursor << rowLine;

	cursor.nextLine();
	cursor << verticalBar << "　玩家　";
	cursor << Color::B_BLUE  << left << setw(16) << "1" << Color::DEF_COLOR << verticalBar;
	cursor << Color::B_GREEN << left << setw(16) << "2" << Color::DEF_COLOR << verticalBar;
	cursor << Color::B_CYAN << left << setw(16) << "2" << Color::DEF_COLOR << verticalBar;
	cursor << Color::B_RED << left << setw(16) << "2" << Color::DEF_COLOR << verticalBar;
	cursor.nextLine();

	cursor << verticalBar << "　現金　";
	cursor << " " << left << setw(15) << dollarinfo[0] << verticalBar;
	cursor << " " << left << setw(15) << dollarinfo[3] << verticalBar;
	cursor << " " << left << setw(15) << dollarinfo[6] << verticalBar;
	cursor << " " << left << setw(15) << dollarinfo[9] << verticalBar;
	cursor.nextLine();

	cursor << verticalBar << "　借款　";
	cursor << " " << left << setw(15) << dollarinfo[1] << verticalBar;
	cursor << " " << left << setw(15) << dollarinfo[4] << verticalBar;
	cursor << " " << left << setw(15) << dollarinfo[7] << verticalBar;
	cursor << " " << left << setw(15) << dollarinfo[10] << verticalBar;
	cursor.nextLine();

	cursor << verticalBar << "　存款　";
	cursor << " " << left << setw(15) << dollarinfo[2] << verticalBar;
	cursor << " " << left << setw(15) << dollarinfo[5] << verticalBar;
	cursor << " " << left << setw(15) << dollarinfo[8] << verticalBar;
	cursor << " " << left << setw(15) << dollarinfo[11] << verticalBar;
	cursor.nextLine();
	cout << rowLine;
}

void Draw::showcurrentplayer() {
	Cursor cursor(0, 40);
	cursor << verticalBar << "目前遊戲者" << setw(58) << " " << "當前回合數" << verticalBar;
	cursor.nextLine();
	cursor << verticalBar << " " << "1" << setw(75) << " " << "1" << verticalBar;
	cursor.nextLine();
	cursor << rowLine;
}

