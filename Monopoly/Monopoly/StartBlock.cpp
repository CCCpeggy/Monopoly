#include "StartBlock.h"
#include"Player.h"
#include<iostream>
#include"Game.h"
#define �g�L�_�I������B 2000



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
	player->earnMoney(�g�L�_�I������B);
	stringstream ss;
	ss<< "��o " << �g�L�_�I������B << " ��";
	Game::showDialog("�g�L�_�I",ss.str());
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
	cursor << "�g�a�W�١G" << name;
	cursor.nextLine().nextLine();
	cursor << "�O�_�����١G";
	getHasRoadBlock() ? cursor << "�O" : cursor << "�_";
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