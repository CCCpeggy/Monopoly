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
const string Draw::infoBlock[18] = {
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
const string Draw::gameStatusFrame[9] = {
"．———————————————————————————————————————．"
,"｜　玩家　                ｜                ｜                ｜                ｜"
,"｜　現金　                ｜                ｜                ｜                ｜"
,"｜　借款　                ｜                ｜                ｜                ｜"
,"｜　存款　                ｜                ｜                ｜                ｜"
,"．———————————————————————————————————————．"
,"｜目前遊戲者                                                          當前回合數｜"
,"｜                                                                              ｜"
,"．———————————————————————————————————————．" };
const string Draw::number[10] = { "１", "２", "３", "４", "５", "６", "７", "８", "９", "０" };
const string Draw::playInfoTitle[5] = { "　總覽　","　資金　", "　地產　", "　股票　", "　道具　" };
const int Draw::FIRST = true;
const int Draw::SECOND = false;


#define DIALOG_CONTENT_LEN 46
#define DIALOG_TITLE_LEN 50
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

void Draw::drawDialogueBox(string title, int num, string unit)
{
	//TODO: 顯示數字對話框
	Cursor cursor(15, 10);
	cursor << pair<string, int> (title, DIALOG_TITLE_LEN);
	cursor.nextLine();
	for (int i = 0; i <= 9; i++)
	{
		cursor << dialogueBox[i];
		cursor.nextLine();
	}
	stringstream ss;
	ss << num << unit;
	cursor.add(0, 4);
	cursor << pair<string, int>(ss.str(), DIALOG_TITLE_LEN);
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

void Draw::drawMenu(vector<string> itemList, string name, int index)
{
	//TODO:選單
	Cursor cursor(15, 10);
	cursor << pair<string, int>(name, DIALOG_TITLE_LEN);
	cursor.nextLine();
	for (int i = 0; i <= 9; i++)
	{
		cursor << dialogueBox[i];
		cursor.nextLine();
	}
	cursor.add(2, 3);
	for (int i = 0; i < itemList.size(); i++)
	{
		if (i == index) cursor << Color::TAG_CHOOSE_COLOR;
		else cursor << Color::DEF_COLOR;
		cursor << pair<string, int>(itemList[i], DIALOG_CONTENT_LEN);
		cursor.nextLine();
	}
}

void Draw::drawPlayerInfoTitle(int index)
{
	Cursor cursor(18, 9, 10);
	for (int i = 0; i < 5; i++) {
		if (i == index) cursor << Color::TAG_CHOOSE_COLOR;
		else cursor << Color::DEF_COLOR;
		cursor << pair<string, int>(playInfoTitle[i], 4);
		cursor.nextPos();
	}
}

void Draw::drawPlayerInfoFrame()
{
	Cursor cursor(16, 7);
	cursor << pair<string, int>(" 玩　家　資　訊 ", 49);
	for (int i = 0; i <= 17; i++)
	{
		cursor.nextLine();
		cursor << Draw::infoBlock[i];
	}
}

void Draw::drawGameStatusFrame()
{
	Cursor cursor(0, 34);
	for (int i = 0; i < 9; i++) {
		cursor << gameStatusFrame[i];
		cursor.nextLine();
	}
}

void Draw::cleanCenter()
{
	string nothing = "　　　　　　　　　　　　　　　　　　　　　　　　　　　　";
	Cursor cursor(14, 5);
	for (int i = 0; i <= 22; i++)
	{
		cursor << nothing;
		cursor.nextLine();
	}
}

void Draw::cleanPlayerInfoContent()
{
	string nothing = "　　　　　　　　　　　　　　　　　　　　　　　　";
	Cursor cursor(18, 11);
	for (int i = 0; i <= 13; i++)
	{
		cursor << nothing;
		cursor.nextLine();
	}
}

