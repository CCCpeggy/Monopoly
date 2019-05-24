#include "FateBlock.h"
#include "Card.h"
#include "Player.h"
#include <iostream>
using namespace std;
FateBlock& FateBlock::operator=(FateBlock& block)
{
	BaseBlock::operator=(block);
	return *this;
}

void FateBlock::startEvent(Player*)
{
}

void FateBlock::arriveEvent(Player* player)
{
	if (fateCards.size()>=1)
	{
		fateCards[fateCards.size() - 1].event(player);
		fateCards.pop_back();
	}
	else
	{
		Game::showDialog("命運", "沒有命運卡了");
	}
}

void FateBlock::throughEvent(Player* player)
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

