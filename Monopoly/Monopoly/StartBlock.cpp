#include "StartBlock.h"
#include"Player.h"
#include<iostream>
#define 經過起點獲取金額 2000



void StartBlock::arrive(Player* p)
{
	cout << "ARRIVE START" << endl;
	output();
	p->outputInformation();
	return;
}

void StartBlock::through(Player* p)
{
	p->earnMoney(經過起點獲取金額);
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
