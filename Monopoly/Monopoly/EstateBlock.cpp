#include "EstateBlock.h"
#include "Player.h"
#include <iostream>
void EstateBlock::arrive(Player* player)
{
	cout << "ARRIVE Estate" << endl;
	output();
	if (this->owner!=NULL)
	{
		player->giveMoney(*owner, tolls[houseLevel]);
	}
	else
	{
		//�߰ݬO�_�n�R�a return bool
		char buychar;
		cout << "�O�_�n�R�a(����:" << initialPrice << ")(Y/N)" << endl;
		cin >> buychar;
		if (buychar=='Y'|| buychar == 'y')
		{
			cout << "�ʶR���\" << endl;
			player->buyHouse(*this);
			this->owner = player;
		}
		else
		{
			return;
		}
	}
}

void EstateBlock::through(Player* player)
{
	player->outputInformation();
	if (true)//�Y������
	{
		//dosomething
	}
	return;
}

EstateBlock& EstateBlock::operator=( EstateBlock& estate)
{
		BaseBlock::operator=(estate);
		houseLevel = estate.houseLevel;
		initialPrice = estate.initialPrice;
		owner = estate.owner;
		tolls = estate.tolls;
		return *this;
	// TODO: �󦹳B���J�Ǧ^���z��
}

EstateBlock::EstateBlock(int newIndex,string newName, int newInitialPrice, int* newTolls, Player* newOwner, int newHouseLevel):
	BaseBlock(newName,newIndex),initialPrice(newInitialPrice),tolls(newTolls),owner(newOwner),houseLevel(newHouseLevel)
{
}

EstateBlock::EstateBlock():BaseBlock(),houseLevel(-1),initialPrice(0),owner(NULL)
{
}



EstateBlock::~EstateBlock()
{
}
