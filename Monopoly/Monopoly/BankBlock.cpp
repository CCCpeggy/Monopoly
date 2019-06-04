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

	Game::showDialog("�g�L�Ȧ�", "�i�H�i������ާ@");
	//TODO:�ާ@���O
	pair<vector<string>, std::map<int, bool(Game::*)(void)> > action;
	bool doNext;
	int choose;
	do {
		action = game->getAction(�Ȧ�);
		choose = game->showMenu("�п�ܰʧ@", action.first);
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
	cursor << "�g�a�W�١G" << name;
	cursor.nextLine().nextLine();
	cursor << "�O�_�����١G";
	getHasRoadBlock() ? cursor << "�O" : cursor << "�_";
}
