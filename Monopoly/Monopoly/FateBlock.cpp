#include "FateBlock.h"
#include "Card.h"
#include "Player.h"
#include <iostream>
using namespace std;
const string FateBlock::card[] = { "銀行付你利息，500元","經營小本生意，獲利1000元","整修自己所有房屋，每棟250元","這是你的生日，向每人收取禮金1000元" };
int FateBlock::getCategory()
{
	return -1;
}
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
	int index = rand() % 4;
	Game::showDialog("命運", card[index]);
	Player* currentPlayer = game->getPlayer();
	int total = 0;
	switch (index)
	{
	case 0://銀行付你利息，500元
		currentPlayer->earnMoney(500);
		break;
	case 1://經營小本生意，獲利1000元
		currentPlayer->earnMoney(1000);
		break;
	case 2://整修自己所有房屋，每棟250元
		currentPlayer->loseMoney(currentPlayer->getTotalHouse() * 250);
		break;
	case 3://這是你的生日，向每人收取禮金1000元
		game->getMoneyFromEveryPlayer(1000);
		break;
	}
}

void FateBlock::throughEvent(Player* player)
{
	player->outputInformation();
	return;
}

FateBlock::FateBlock(int newIndex, string newName, Game* game):BaseBlock(newName,newIndex),game(game)
{
}

FateBlock::FateBlock(Game* game): game(game)
{
}


FateBlock::~FateBlock()
{
}


void FateBlock::OutputBlockInfo()
{
	Cursor cursor = Draw::dialogCursor.getSubCursor(18, 8, 12);
	cursor << "土地名稱：" << name;
	cursor.nextLine().nextLine();
}
