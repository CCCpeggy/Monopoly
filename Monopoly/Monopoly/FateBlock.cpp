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
	Draw fate;
	srand(time(NULL));
	int index = rand() % 4 + 1;
	fate.drawDialogueBox("�R�B", card[index]);
	
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

