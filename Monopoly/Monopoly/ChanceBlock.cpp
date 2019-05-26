#include "ChanceBlock.h"
#include "Card.h"
#include "Player.h"
#include<iostream>
#include "Draw.h"
#include "Game.h"
#include "EstateBlock.h"
using namespace std;
const string ChanceBlock::card[] = {"銀行付你利息，500元","經營小本生意，獲利1000元","整修自己所有房屋，每棟250元","這是你的生日，向每人收取禮金1000元"};
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
	Draw chance;
	srand(time(NULL));
	int index = rand() % 4+1;
	chance.drawDialogueBox("機會",card[index]);
	vector<EstateBlock*>::iterator it = player->ownedEstates.begin();
	int total = 0;
	switch (index)
	{
	case 0://銀行付你利息，500元
		player->earnMoney(2000);
		break;
	case 1://經營小本生意，獲利1000元
		player->earnMoney(1000);
		break;
	case 2://整修自己所有房屋，每棟250元
		for (; it != player->ownedEstates.end(); it++)
		{
			if ((*it)->houseLevel != 0 && (*it)->houseLevel != -1) { total = total + (*it)->houseLevel; }
		}
		player->loseMoney(total*250);
		break;
	case 3:
		break;
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
