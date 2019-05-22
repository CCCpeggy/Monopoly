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

void ChanceBlock::arrive(Player* player)
{
	if (chanceCards.size() >= 1)
	{
		chanceCards[chanceCards.size() - 1].event(player);
		chanceCards.pop_back();
	}
	else
	{
		cout << "�S�����|�d�F" << endl;
	}
}

void ChanceBlock::through(Player*)
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