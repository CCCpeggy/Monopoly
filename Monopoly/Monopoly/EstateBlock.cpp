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
		//draw �߰ݬO�_�n�R�a return bool
		char buychar;
		cout << "�O�_�n�R�a(����:" << initialPrice << ")(Y/N)" << endl;
		cin >> buychar;
		if (buychar=='Y'|| buychar == 'y')
		{
			cout << "�ʶR���\" << endl;
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
	if (true)//�Y������
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
