#include "StartBlock.h"
#include"Player.h"
#include<iostream>
#define �g�L�_�I������B 2000



void StartBlock::arrive(Player* p)
{
	cout << "ARRIVE START" << endl;
	output();
	p->outputInformation();
	return;
}

void StartBlock::through(Player* p)
{
	p->earnMoney(�g�L�_�I������B);
	p->outputInformation();
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