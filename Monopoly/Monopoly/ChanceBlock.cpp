#include "ChanceBlock.h"
#include "Card.h"
#include "Player.h"
#include<iostream>
#include "Draw.h"
#include "Game.h"
#include "EstateBlock.h"
using namespace std;
const string ChanceBlock::card[] = {"銀行付你利息，500元","經營小本生意，獲利1000元","整修自己所有房屋，每棟250元","這是你的生日，向每人收取禮金1000元","繳稅，付出總資產10%的稅金"};
int ChanceBlock::getCategory()
{
	return -2;
}
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
	int index = rand() % 5;
	Game::showDialog("機會", card[index]);
	vector<EstateBlock*>::iterator it = player->ownedEstates.begin();
	int total = 0;
	switch (index)
	{
	case 0://銀行付你利息，500元
		game->getPlayer()->earnMoney(500);
		break;
	case 1://經營小本生意，獲利1000元
		game->getPlayer()->earnMoney(1000);
		break;
	case 2://整修自己所有房屋，每棟250元
		for (; it != player->ownedEstates.end(); it++)
		{
			if ((*it)->houseLevel != 0 && (*it)->houseLevel != -1) { total = total + (*it)->houseLevel; }
		}
		game->getPlayer()->loseMoney(total*250);
		break;
	case 3://這是你的生日，向每人收取禮金1000元
		game->getMoneyFromEveryPlayer(1000);
		break;
	case 4://繳稅，付出總資產10%的稅金
		game->getPlayer()->loseMoney(game->getPlayer()->getAsset()*0.1);
		break;
	}
}

void ChanceBlock::throughEvent(Player*)
{
	return;
}

ChanceBlock::ChanceBlock(int newIndex, string newName, Game * game) :BaseBlock(newName, newIndex), game(game)
{
}

ChanceBlock::ChanceBlock(Game* game):game(game)
{
}


ChanceBlock::~ChanceBlock()
{
}

void ChanceBlock::drawBlockInfoCenter()
{
	Cursor cursor = Draw::dialogCursor.getSubCursor(18, 10, 12);
	cursor << "土地名稱：" << name;
	cursor.nextLine().nextLine();
	cursor << "是否有路障：";
	getHasRoadBlock() ? cursor << "是" : cursor << "否";
}
