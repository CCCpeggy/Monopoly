#include "FateBlock.h"
#include "Card.h"
#include "Player.h"
#include <iostream>
using namespace std;
const string FateBlock::card[] = { "�P���v���A�g�Įv���A����2000��","��18%�A��o�s��18%���Q��","�y�ձ߷|�����u�A��o500��","�����a�訤�Y�A�V�C�H�����O�@�O1000��","�ߨ�D��A��o����1��","�ߨ�D��A��o������l1��" };
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
	Game::showDialog("�R�B", card[index]);
	Player* currentPlayer = game->getPlayer();
	int total = 0;
	switch (index)
	{
	case 0://�P���v���A�g�Įv���A����2000��
		currentPlayer->loseMoney(2000);
		break;
	case 1://�⢰��%�A��o�s�ڢ����H���Q��
		currentPlayer->earnMoney(currentPlayer->getSaving()*0.18);
		break;
	case 2://�y�ձ߷|�����u�A��o500��
		currentPlayer->earnMoney(500);
		break;
	case 3://�����a�訤�Y�A�V�C�H�����O�@�O1000��
		game->getMoneyFromEveryPlayer(1000);
		break;
	case 4://�ߨ�D��A��o����1��
		currentPlayer->addItem(0);
	case 5://�ߨ�D��A��o������l1��
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
	cursor << "�g�a�W�١G" << name;
	cursor.nextLine().nextLine();
	cursor << "�O�_�����١G";
	getHasRoadBlock() ? cursor << "�O" : cursor << "�_";
}
