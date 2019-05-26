#include "FateBlock.h"
#include "Card.h"
#include "Player.h"
#include <iostream>
using namespace std;
const string FateBlock::card[] = { "�Ȧ�I�A�Q���A500��","�g��p���ͷN�A��Q1000��","��צۤv�Ҧ��ЫΡA�C��250��","�o�O�A���ͤ�A�V�C�H����§��1000��" };
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
	int index = rand() % 4 + 1;
	Game::showDialog("�R�B", card[index]);
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
		player->loseMoney(total * 250);
		break;
	case 3://
		break;
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

