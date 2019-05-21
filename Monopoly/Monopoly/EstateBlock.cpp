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
		//詢問是否要買地 return bool
		char buychar;
		cout << "是否要買地(價格:" << initialPrice << ")(Y/N)" << endl;
		cin >> buychar;
		if (buychar=='Y'|| buychar == 'y')
		{
			cout << "購買成功" << endl;
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
	if (true)//若有路障
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
	// TODO: 於此處插入傳回陳述式
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
