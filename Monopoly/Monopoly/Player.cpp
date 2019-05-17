#include "Player.h"
#include "BaseBlock.h"
#include "EstateBlock.h"
#include <time.h>
#include<iostream>
using namespace std;
void Player::gotoNextBlock(int blockNums)
{
	location = location->nextBlock;

}
void Player::arriveBlock()
{
	location->arrive(this);
}

int Player::getMoney()
{
	return money;
}

int Player::getDebit()
{
	return debit;
}

int Player::getSaving()
{
	return saving;
}

void Player::rollDice(int blockNums)
{
	srand(time(NULL));
	int dicePoint = rand() % 6 + 1 + rand() % 6 + 1;
	cout << "Player 擲出了" << dicePoint << "點" << endl;
	for (size_t i = 0; i < dicePoint-1; i++)
	{
		gotoNextBlock(blockNums);
		location->through(this);
	}
	gotoNextBlock(blockNums);
	arriveBlock();
}


Player::Player(int newMoney, int newDebit, int newSaving, BaseBlock* newLocation):money(newMoney),debit(newDebit),saving(newSaving),location(newLocation)
{

}


Player::~Player()
{
}

void Player::earnMoney(int m)
{
	money += m;
}

void Player::giveMoney(Player& p, int m)
{
	p.earnMoney(m);
	money -= m;
}

void Player::buyHouse(EstateBlock& estate)
{
	ownEstates.push_back(&estate);
	if (estate.houseLevel==-1)
	{
		money -= estate.initialPrice;
	}
	else
	{
		money -= (int)(estate.initialPrice*0.5);
	}
	estate.houseLevel++;
}

void Player::outputInformation()
{
	cout <<	"玩家金錢:" << getMoney() <<"   ";
	cout << "現在位置"<< location->index << endl;
}
