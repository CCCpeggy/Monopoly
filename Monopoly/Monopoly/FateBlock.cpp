#include "FateBlock.h"
#include "Card.h"
#include "Player.h"
#include <iostream>
using namespace std;
const string FateBlock::card[] = { "銀行付你利息，500元","經營小本生意，獲利1000元","整修自己所有房屋，每棟250元","這是你的生日，向每人收取禮金1000元" };
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
	fate.drawDialogueBox("命運", card[index]);
	
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

