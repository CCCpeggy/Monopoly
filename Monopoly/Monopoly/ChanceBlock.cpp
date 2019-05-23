#include "ChanceBlock.h"
#include "Card.h"
#include "Player.h"
#include<iostream>
using namespace std;
ChanceBlock& ChanceBlock::operator=(ChanceBlock& chance)
{
	BaseBlock::operator=(chance);
	return *this;
}

void ChanceBlock::startEvent(Player*)
{
}

void ChanceBlock::arriveEvent(Player* player)
{
	if (chanceCards.size() >= 1)
	{
		chanceCards[chanceCards.size() - 1].event(player);
		chanceCards.pop_back();
	}
	else
	{
		cout << "沒有機會卡了" << endl;
	}
}

void ChanceBlock::throughEvent(Player*)
{
	return;
}

ChanceBlock::ChanceBlock(int newIndex, string newName) :BaseBlock(newName, newIndex)
{
}

ChanceBlock::ChanceBlock()
{
}


ChanceBlock::~ChanceBlock()
{
}
