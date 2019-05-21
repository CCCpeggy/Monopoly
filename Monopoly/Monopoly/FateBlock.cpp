#include "FateBlock.h"
#include "Card.h"
#include "Player.h"
#include<iostream>
using namespace std;
FateBlock& FateBlock::operator=(FateBlock& block)
{
	BaseBlock::operator=(block);
	return *this;
}

void FateBlock::arrive(Player* player)
{
	if (fateCards.size()>=1)
	{
		fateCards[fateCards.size() - 1].event(player);
		fateCards.pop_back();
	}
	else
	{
		cout << "沒有命運卡了" << endl;
	}
}

void FateBlock::through(Player* player)
{
	player->outputInformation();
	return;
}

FateBlock::FateBlock(int newIndex, string newName):BaseBlock(newName,newIndex)
{
}

FateBlock::FateBlock()
{
}


FateBlock::~FateBlock()
{
}