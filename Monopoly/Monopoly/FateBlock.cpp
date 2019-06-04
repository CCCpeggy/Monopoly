#include "FateBlock.h"
#include "Card.h"
#include "Player.h"
#include <iostream>
using namespace std;
const string FateBlock::card[] = { "�Ȧ�I�A�Q���A500��","�g��p���ͷN�A��Q1000��","��צۤv�Ҧ��ЫΡA�C��250��","�o�O�A���ͤ�A�V�C�H����§��1000��" };
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
	Game::showDialog("�R�B", card[index]);
	Player* currentPlayer = game->getPlayer();
	int total = 0;
	switch (index)
	{
	case 0://�Ȧ�I�A�Q���A500��
		currentPlayer->earnMoney(500);
		break;
	case 1://�g��p���ͷN�A��Q1000��
		currentPlayer->earnMoney(1000);
		break;
	case 2://��צۤv�Ҧ��ЫΡA�C��250��
		currentPlayer->loseMoney(currentPlayer->getTotalHouse() * 250);
		break;
	case 3://�o�O�A���ͤ�A�V�C�H����§��1000��
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
	cursor << "�g�a�W�١G" << name;
	cursor.nextLine().nextLine();
}
