#include "BaseBlock.h"
#include "EstateBlock.h"
#include "Player.h"
#include <iostream>
void EstateBlock::arrive(Player* p)
{
	cout << "ARRIVE Estate" << endl;
	output();
	if (this->owner!=NULL)
	{
		p->giveMoney(*owner, tolls[houseLevel]);
	}
	else
	{
		//draw 詢問是否要買地 return bool
		char buychar;
		cout << "是否要買地(價格:" << initialPrice << ")(Y/N)" << endl;
		cin >> buychar;
		if (buychar=='Y'|| buychar == 'y')
		{
			cout << "購買成功" << endl;
			p->buyHouse(*this);
			this->owner = p;
		}
		else
		{
			return;
		}
	}
}

void EstateBlock::through(Player* p)
{
	p->outputInformation();
	if (true)//若有路障
	{
		//dosomething
	}
	return;
}

EstateBlock& EstateBlock::operator=( EstateBlock& b)
{
		BaseBlock::operator=(b);
		houseLevel = b.houseLevel;
		initialPrice = b.initialPrice;
		owner = b.owner;
		tolls = b.tolls;
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
