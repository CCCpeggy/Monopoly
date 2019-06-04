#include "BankBlock.h"
#include "Game.h"


int BankBlock::getCategory()
{
	return 2;
}

void BankBlock::startEvent(Player*)
{
}

void BankBlock::arriveEvent(Player*)
{
}

void BankBlock::throughEvent(Player* player)
{

	Game::showDialog("經過銀行", "可以進行相關操作");
	//TODO:操作面板
	pair<vector<string>, std::map<int, bool(Game::*)(void)> > action;
	bool doNext;
	int choose;
	do {
		action = game->getAction(銀行);
		choose = game->showMenu("請選擇動作", action.first);
		doNext = (game->*action.second[choose])();
	} while (!doNext);
	return;
}

BankBlock& BankBlock::operator=(const BankBlock& b)
{
	BaseBlock::operator=(b);
	return *this;
}

BankBlock::BankBlock(string newName, int newIndex, Game *game) :BaseBlock(newName, newIndex),game(game)
{
}

BankBlock::BankBlock()
{
}


BankBlock::~BankBlock()
{
}

void BankBlock::drawBlockInfoCenter()
{
	Cursor cursor = Draw::dialogCursor.getSubCursor(18, 8, 12);
	cursor << "土地名稱：" << name;
	cursor.nextLine().nextLine();
	cursor << "是否有路障：";
	getHasRoadBlock() ? cursor << "是" : cursor << "否";
}
