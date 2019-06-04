#include "FateBlock.h"
#include "Card.h"
#include "Player.h"
#include <iostream>
using namespace std;
const string FateBlock::card[] = { "感恩師父，讚嘆師父，捐款2000元","領18%，獲得存款18%的利息","造勢晚會走路工，獲得500元","成為地方角頭，向每人收取保護費1000元","撿到道具，獲得路障1個","撿到道具，獲得遙控骰子1個" };
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
	int index = rand() % 6;
	Game::showDialog("命運", card[index]);
	Player* currentPlayer = game->getPlayer();
	int total = 0;
	switch (index)
	{
	case 0://感恩師父，讚嘆師父，捐款2000元
		currentPlayer->loseMoney(2000);
		break;
	case 1://領１８%，獲得存款１８％的利息
		currentPlayer->earnMoney(currentPlayer->getSaving()*0.18);
		break;
	case 2://造勢晚會走路工，獲得500元
		currentPlayer->earnMoney(500);
		break;
	case 3://成為地方角頭，向每人收取保護費1000元
		game->getMoneyFromEveryPlayer(1000);
		break;
	case 4://撿到道具，獲得路障1個
		currentPlayer->addItem(0);
	case 5://撿到道具，獲得遙控骰子1個
		currentPlayer->addItem(1);
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


void FateBlock::drawBlockInfoCenter()
{
	Cursor cursor = Draw::dialogCursor.getSubCursor(18, 10, 12);
	cursor << "土地名稱：" << name;
	cursor.nextLine().nextLine();
	cursor << "是否有路障：";
	getHasRoadBlock() ? cursor << "是" : cursor << "否";
}
