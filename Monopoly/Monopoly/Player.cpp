#include "Player.h"
#include "BaseBlock.h"
#include "EstateBlock.h"
#include "Stock.h"
#include "Game.h"
#include <time.h>
#include<iostream>
using namespace std;
void Player::gotoNextBlock()
{
	location = location->nextBlock;

}
void Player::arriveBlock()
{
	location->arriveEvent(this);
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

pair<int, int> Player::rollDice()
{
	srand(time(NULL));
	int dicePoint1 = rand() % 6 + 1;
	int dicePoint2 = rand() % 6 + 1;
	cout << "Player 擲出了" << dicePoint1<<"+"<<dicePoint2 << "點" << endl;
	return pair<int, int>(dicePoint1, dicePoint2);
	
}

void Player::moveForwardByStep(int step)
{
	location->startByThisBlock(this);
	for (int i = 1; i <step; i++)
	{
		gotoNextBlock();
		location->throughThisBlock(this);
	}
	gotoNextBlock();
	location->arriveThisBlock(this);
}

void Player::moveToBlock(BaseBlock* block)
{
	location = block;
	location->arriveEvent(this);
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

void Player::sellEstate(EstateBlock* estate)
{
	for (size_t i = 0; i < ownedEstates.size(); i++)
	{
		if (ownedEstates[i]==estate)
		{
			ownedEstates.erase(ownedEstates.begin() + i);
			earnMoney(estate->beSelled());
			//cout<<"賣出房地產:"<<estate->name<<endl;
			return;
		}
	}
}

void Player::buyHouse(EstateBlock * estate)
{
	ownedEstates.push_back(estate);
	if (estate->houseLevel==-1)
	{
		money -= estate->initialPrice;
	}
	else
	{
		money -= (int)(estate->initialPrice*0.5);
	}
	estate->houseLevel++;
}

void Player::outputInformation()
{
	cout <<	"玩家金錢:" << getMoney() <<"   ";
	cout << "現在位置"<< location->index << endl;
}
