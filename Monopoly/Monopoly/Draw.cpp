#include "Draw.h"

extern HANDLE handleOutput;

const Cursor Draw::cursor(0, 0, 10, 4);
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
const string Draw::boundary[34] = { "．－－－－．－－－－．－－－－．－－－－．－－－－．－－－－．－－－－．－－－－．",
											 "∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣",
											 "∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣",
											 "∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣",
											 "．－－－－．－－－－．－－－－．－－－－．－－－－．－－－－．－－－－．－－－－．",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "．－－－－．　　　　　　　　　　　　　　　　　　　　　　　　　　　　　．－－－－．",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "．－－－－．　　　　　　　　　　　　　　　　　　　　　　　　　　　　　．－－－－．",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											  "．－－－－．　　　　　　　　　　　　　　　　　　　　　　　　　　　　　．－－－－．",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											  "．－－－－．　　　　　　　　　　　　　　　　　　　　　　　　　　　　　．－－－－．",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											  "．－－－－．　　　　　　　　　　　　　　　　　　　　　　　　　　　　　．－－－－．",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "．－－－－．－－－－．－－－－．－－－－．－－－－．－－－－．－－－－．－－－－．",
											 "∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣",
											 "∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣",
											 "∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣",
											 "．－－－－．－－－－．－－－－．－－－－．－－－－．－－－－．－－－－．－－－－．"
};
const string Draw::number[10] = { "１", "２", "３", "４", "５", "６", "７", "８", "９", "０" };
const int Draw::FIRST = true;
const int Draw::SECOND = false;


#define DIALOG_CONTENT_LEN 46
void Draw::drawDialogueBox(string title, pair<string, string> chooseName, bool status)
{
	Cursor cursor(15, 10);
	for (int i = 0; i <= 9; i++)
	{
		cursor << dialogueBox[i];
		cursor.nextLine();
	}

	cursor.add(2,2);
	cursor << pair<string, int>(title, DIALOG_CONTENT_LEN);

	cursor.add(0, 5, DIALOG_CONTENT_LEN / 2);
	if (status == FIRST)
	{
		cursor << Color::TAG_CHOOSE_COLOR << pair<string, int>(chooseName.first, DIALOG_CONTENT_LEN/2);
		cursor.nextPos();
		cursor << Color::DEF_COLOR << pair<string, int>(chooseName.second, DIALOG_CONTENT_LEN / 2);
	}
	else if (status == SECOND)
	{
		cursor << Color::DEF_COLOR << pair<string, int>(chooseName.first, DIALOG_CONTENT_LEN / 2);
		cursor.nextPos();
		cursor << Color::TAG_CHOOSE_COLOR << pair<string, int>(chooseName.second, DIALOG_CONTENT_LEN / 2);
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

void Draw::drawPlayerList(vector<int> dollarinfo)
{
	Cursor cursor(0, 34);
	cursor << rowLine;

	cursor.nextLine();
	cursor << verticalBar << "　玩家　";
	cursor << Color::B_BLUE  << left << setw(16) << "1" << Color::DEF_COLOR << verticalBar;
	cursor << Color::B_GREEN << left << setw(16) << "2" << Color::DEF_COLOR << verticalBar;
	cursor << Color::B_CYAN << left << setw(16) << "3" << Color::DEF_COLOR << verticalBar;
	cursor << Color::B_RED << left << setw(16) << "4" << Color::DEF_COLOR << verticalBar;
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

void Draw::drawCurrentPlayer(int playerIndex, int round)
{
	stringstream ss;
	ss << playerIndex;
	Cursor cursor(0, 40);
	cursor << verticalBar << "目前遊戲者" << setw(58) << " " << "當前回合數" << verticalBar;
	cursor.nextLine();
	cursor << verticalBar << setw(2) << playerIndex << setw(75) << " " << round << verticalBar;
	cursor.nextLine();
	cursor << rowLine;
}

void Draw::drawMap()
{
	Cursor cursor(0, 0);
	
	for (int i = 0; i < 34; i++)
	{
		cursor << boundary[i];
		cursor.nextLine();
	}
}

void Draw::drawDice(int dice1, int dice2)
{
	//TODO: 畫骰子
	Cursor cursor(15, 10);
	for (int i = 0; i <= 9; i++)
	{
		cursor << dialogueBox[i];
		cursor.nextLine();
	}
	cursor.add(DIALOG_CONTENT_LEN / 2 - 1, 4).inputPos(0, 0);
	cout << dice1 << " " << dice2;
}

void Draw::drawMenu(vector<string> items, string name, int index)
{
	//TODO:選單
	Cursor cursor(15, 10);
	cursor << pair<string, int>(name, DIALOG_CONTENT_LEN);
	cursor.nextLine();
	for (int i = 0; i <= 9; i++)
	{
		cursor << dialogueBox[i];
		cursor.nextLine();
	}
	cursor.add(2, 3);
	for (int i = 0; i < items.size(); i++)
	{
		if (i == index) cursor << Color::TAG_CHOOSE_COLOR;
		else cursor << Color::DEF_COLOR;
		cursor << items[i];
		cursor.nextLine();
	}
}

void Draw::cleanCenter()
{
	string nothing = "　　　　　　　　　　　　　　　　　　　　　　　　　　　　";
	Cursor cursor(14, 5);
	for (int i = 5; i <= 27; i++)
	{
		cursor << nothing;
		cursor.nextLine();
	}
}

