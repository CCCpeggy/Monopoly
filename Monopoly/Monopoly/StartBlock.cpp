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
