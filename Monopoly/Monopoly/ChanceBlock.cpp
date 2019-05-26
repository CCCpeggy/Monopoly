#include "ChanceBlock.h"
#include "Card.h"
#include "Player.h"
#include<iostream>
#include "Draw.h"
#include "Game.h"
#include "EstateBlock.h"
using namespace std;
const string ChanceBlock::card[] = {"�Ȧ�I�A�Q���A500��","�g��p���ͷN�A��Q1000��","��צۤv�Ҧ��ЫΡA�C��250��","�o�O�A���ͤ�A�V�C�H����§��1000��"};
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
	chance.drawDialogueBox("���|",card[index]);
	vector<EstateBlock*>::iterator it = player->ownedEstates.begin();
	int total = 0;
	switch (index)
	{
	case 0://�Ȧ�I�A�Q���A500��
		player->earnMoney(2000);
		break;
	case 1://�g��p���ͷN�A��Q1000��
		player->earnMoney(1000);
		break;
	case 2://��צۤv�Ҧ��ЫΡA�C��250��
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
