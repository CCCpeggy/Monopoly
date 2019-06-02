#include "Draw.h"

extern HANDLE handleOutput;
const string Draw::playerEstateInfoTitle[3] = { "名稱","等級","過路費" };
const string Draw::playerStockInfoTitle[3] = { "名稱","張數","股價" };
const string Draw::stockInfoTitle[3] = { "名稱","股價","漲跌" };
const Cursor Draw::cursor(50, 0, 10, 4);
Cursor Draw::playerStatusCursor(0, 34);
Cursor Draw::dialogCursor(65, 5);
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
const string Draw::stockInfoBlock[18] = {
										   "■————————————————————————■",
										   "∥　　　　　　　　　　　　　　　　　　　　　　　　∥",
											"∥————————————————————————∥"  ,
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
const string Draw::boundary[5] = { "．－－－－．"
									,"∣　　　　∣"
									,"∣　　　　∣"
									,"∣　　　　∣"
									,"．－－－－．"
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
const string Draw::houseLevelSymbol[4] = { "零","壹","貳","參" };
const string Draw::diceone[5] = { "．———．",
							"｜　　　｜",
							"｜　●　｜",
							"｜　　　｜",
							"．———．" };
const string Draw::dicetwo[5] = { "．———．",
							"｜　●　｜",
							"｜　　　｜",
							"｜　●　｜",
							"．———．" };
const string Draw::dicethree[5] = { "．———．",
							"｜　●　｜",
							"｜　●　｜",
							"｜　●　｜",
							"．———．" };
const string Draw::dicefour[5] = { "．———．",
							"｜●　●｜",
							"｜　　　｜",
							"｜●　●｜",
							"．———．" };
const string Draw::dicefive[5] = { "．———．",
							"｜●　●｜",
							"｜　●　｜",
							"｜●　●｜",
							"．———．" };
const string Draw::dicesix[5] = { "．———．",
							"｜●　●｜",
							"｜●　●｜",
							"｜●　●｜",
							"．———．" };

const int Draw::FIRST = true;
const int Draw::SECOND = false;


#define DIALOG_CONTENT_LEN 46
#define DIALOG_TITLE_LEN 50
void Draw::drawDialogueBox(string title, pair<string, string> chooseName, bool status)
{
	Cursor cursor = dialogCursor.getSubCursor(1, 5);
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
	Cursor cursor = dialogCursor.getSubCursor(1, 5);
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
	Cursor cursor = dialogCursor.getSubCursor(1, 5);
	
	for (int i = 0; i <= 9; i++)
	{
		cursor << dialogueBox[i];
		cursor.nextLine();
	}
	cursor.add(2, 2, DIALOG_CONTENT_LEN /3);
	cursor << pair<string, int>(title, DIALOG_CONTENT_LEN);
	stringstream ss;
	ss << num << unit;
	cursor.nextLine().nextLine().nextLine().nextLine();
	cursor << Color::DEF_COLOR<< pair<string, int>("　－　", DIALOG_CONTENT_LEN / 3);
	cursor.nextPos();
	cursor << Color::TAG_CHOOSE_COLOR << pair<string, int>(ss.str(), DIALOG_CONTENT_LEN / 3);
	cursor.nextPos();
	cursor << Color::DEF_COLOR << pair<string, int>("　＋　", DIALOG_CONTENT_LEN / 3);
}

void Draw::drawMap(int count)
{
	count = count < 7 ? 7 : count;
	playerStatusCursor = cursor.getSubCursor(0, count + 1).add(0, 2);
	int dialogStartPosX = ((count - 1) * cursor.getRightX() - DIALOG_TITLE_LEN) / 2;
	int dialogStartPosY = ((count - 1) * cursor.getRightY() - 22) / 2;
	dialogCursor = cursor.getSubCursor(1, 1).add(dialogStartPosX, dialogStartPosY);
	for (int i = 0; i <= count; i++)
	{
		for (int j = 0; j <= count; j++)
		{
			if (i == 0 || i == count || j == 0 || j == count) {
				Cursor subSursor = cursor.getSubCursor(i, j);
				for (int k = 0; k < 5; k++) {
					subSursor << boundary[k];
					subSursor.nextLine();
				}
			}
			
		}
	}
}

void Draw::drawDice(int dice1, int dice2)
{
	Cursor cursor = dialogCursor.getSubCursor(1, 5);
	for (int i = 0; i <= 9; i++)
	{
		cursor << dialogueBox[i];
		cursor.nextLine();
	}
	cursor.add(2, 3, DIALOG_CONTENT_LEN / 2).inputPos(0, 0);

	for (int i = 0; i < 5; i++) {
		switch (dice1) {
		case 1:
			cursor << pair<string, int>(diceone[i], DIALOG_CONTENT_LEN/2);
			break;
		case 2:
			cursor << pair<string, int>(dicetwo[i], DIALOG_CONTENT_LEN / 2);
			break;
		case 3:
			cursor << pair<string, int>(dicethree[i], DIALOG_CONTENT_LEN / 2);
			break;
		case 4:
			cursor << pair<string, int>(dicefour[i], DIALOG_CONTENT_LEN / 2);
			break;
		case 5:
			cursor << pair<string, int>(dicefive[i], DIALOG_CONTENT_LEN / 2);
			break;
		case 6:
			cursor << pair<string, int>(dicesix[i], DIALOG_CONTENT_LEN / 2);
			break;
		}
		cursor.nextPos();
		switch (dice2) {
		case 1:
			cursor << pair<string, int>(diceone[i], DIALOG_CONTENT_LEN / 2);
			break;
		case 2:
			cursor << pair<string, int>(dicetwo[i], DIALOG_CONTENT_LEN / 2);
			break;
		case 3:
			cursor << pair<string, int>(dicethree[i], DIALOG_CONTENT_LEN / 2);
			break;
		case 4:
			cursor << pair<string, int>(dicefour[i], DIALOG_CONTENT_LEN / 2);
			break;
		case 5:
			cursor << pair<string, int>(dicefive[i], DIALOG_CONTENT_LEN / 2);
			break;
		case 6:
			cursor << pair<string, int>(dicesix[i], DIALOG_CONTENT_LEN / 2);
			break;
		}
		cursor.nextLine();
	}	
}

void Draw::drawMenu(vector<string> itemList, string name, int index)
{
	Cursor cursor = dialogCursor.getSubCursor(1, 4);
	cursor << pair<string, int>(name, DIALOG_TITLE_LEN);
	cursor.nextLine();
	for (int i = 0; i <= 9; i++)
	{
		cursor << dialogueBox[i];
		cursor.nextLine();
	}
	cursor.add(2, 3);
	const int itemCount = 6;
	int itemReminder = itemList.size() % itemCount;
	int count = index / itemCount;
	for (int i = 0; i < itemCount - itemReminder; i++) {
		itemList.push_back("　　　　　　　　　");
	}

	for (int i = 0; i < itemCount; i++) {
		if (i == index % itemCount) cursor << Color::TAG_CHOOSE_COLOR;
		else cursor << Color::DEF_COLOR;
		cursor << pair<string, int>(itemList[i + (count * itemCount)], DIALOG_CONTENT_LEN);
		cursor.nextLine();
	}

	

}

void Draw::drawPlayerInfoTitle(int index)
{
	Cursor cursor = dialogCursor.getSubCursor(2, 4, 10);
	for (int i = 0; i < 5; i++) {
		if (i == index) cursor << Color::TAG_CHOOSE_COLOR;
		else cursor << Color::DEF_COLOR;
		cursor << pair<string, int>(playInfoTitle[i], 4);
		cursor.nextPos();
	}
}

void Draw::drawPlayerInfoFrame()
{
	Cursor cursor = dialogCursor.getSubCursor(0, 2);
	cursor << pair<string, int>(" 玩　家　資　訊 ", 49);
	for (int i = 0; i <= 17; i++)
	{
		cursor.nextLine();
		cursor << Draw::infoBlock[i];
	}
}

void Draw::drawGameStatusFrame()
{
	Cursor cursor = playerStatusCursor.getSubCursor(0, 0);
	for (int i = 0; i < 9; i++) {
		cursor << gameStatusFrame[i];
		cursor.nextLine();
	}
}

void Draw::cleanCenter()
{
	Cursor cursor = dialogCursor.getSubCursor(0, 0);
	string nothing = "　　　　　　　　　　　　　　　　　　　　　　　　　　　";
	for (int i = 0; i <= 22; i++)
	{
		cursor << nothing;
		cursor.nextLine();
	}
}

void Draw::cleanPlayerInfoContent()
{
	Cursor cursor = dialogCursor.getSubCursor(4, 6);
	string nothing = "　　　　　　　　　　　　　　　　　　　　　　　";
	for (int i = 0; i <= 13; i++)
	{
		cursor << nothing;
		cursor.nextLine();
	}
}

void Draw::drawStockInfoFrame()
{
	Cursor cursor = dialogCursor.getSubCursor(0, 2);
	cursor << pair<string, int>(" 股　市　資　訊 ", 49);
	for (int i = 0; i <= 17; i++)
	{
		cursor.nextLine();
		cursor << Draw::stockInfoBlock[i];
	}
}

