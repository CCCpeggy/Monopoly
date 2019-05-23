#include "Player.h"
#include "BaseBlock.h"
#include "EstateBlock.h"
#include "Stock.h"
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
	for (int i = 0; i < dicePoint-1; i++)
	{
		gotoNextBlock(blockNums);
		location->through(this);
	}
	gotoNextBlock(blockNums);
	arriveBlock();
}


void Player::displayPlayerLocation()
{
	static int index = 0;//TODO:改成取player自身的index
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	string displayPlayer[4] = { "１","２","３","４" };

	pair<int, int> pos = POSITION(location->x, location->y);
	COORD initPos;
	initPos.X = pos.first + 2 + (index) * 2;
	initPos.Y = pos.second + 2;
	SetConsoleCursorPosition(hOut, initPos);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::F_PLAYER_COLOR[index]);
	std::cout << displayPlayer[index];
	index++;
}

Player::Player(int newIndex,int newMoney, int newDebit, int newSaving, BaseBlock* newLocation):index(newIndex),money(newMoney),debit(newDebit),saving(newSaving),location(newLocation)
{

}


Player::~Player()
{
}

void Player::tradeStock(Stock* stock, bool buyTrueSellFalse, int quantity)
{
	if (buyTrueSellFalse)
	{
		stock->beOwned[this] += quantity;
		saving -= stock->prize * quantity;
	}
	else
	{
		if (stock->beOwned[this]>=quantity)
		{
			stock->beOwned[this] -= quantity;
			saving += stock->prize * quantity;
		}
	}
}

void Player::earnMoney(int money)
{
	this->money += money;
}

void Player::giveMoney(Player& player, int money)
{
	player.earnMoney(money);
	this->money -= money;
}

void Player::buyHouse(EstateBlock& estate)
{
	ownedEstates.push_back(&estate);
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
