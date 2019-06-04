#include "StartBlock.h"
#include"Player.h"
#include<iostream>
#include"Game.h"
#define 經過起點獲取金額 2000



int StartBlock::getCategory()
{
	return 0;
}

void StartBlock::startEvent(Player* player)
{

}

void StartBlock::arriveEvent(Player* player)
{
	//cout << "ARRIVE START" << endl;
	//output();
	//player->outputInformation();
	return;
}

void StartBlock::throughEvent(Player* player)
{
	player->earnMoney(經過起點獲取金額);
	stringstream ss;
	ss<< "獲得 " << 經過起點獲取金額 << " 元";
	Game::showDialog("經過起點",ss.str());
	//player->outputInformation();
	return;
}

StartBlock& StartBlock::operator=(const StartBlock& b)
{
	BaseBlock::operator=(b);
	return *this;
}

StartBlock::StartBlock(string newName,int newIndex):BaseBlock(newName,newIndex)
{
}


void StartBlock::drawBlockInfoCenter()
{
	Cursor cursor = Draw::dialogCursor.getSubCursor(18, 10, 12);
	cursor << "土地名稱：" << name;
	cursor.nextLine().nextLine();
	cursor << "是否有路障：";
	getHasRoadBlock() ? cursor << "是" : cursor << "否";
}


StartBlock::~StartBlock()
{
}

/*void StartBlock::drawLocationName()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	pair<int, int> pos = POSITION(x, y);
	COORD initPos;
	string tempName = name;
	if (name.length() >= 9)
	{
		tempName.erase(8, tempName.length() - 8);
	}
	initPos.X = pos.first + (9 - tempName.length()) / 2 + 2;
	initPos.Y = pos.second + 1;
	SetConsoleCursorPosition(hOut, initPos);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::DEF_COLOR);
	cout << tempName;
}*/