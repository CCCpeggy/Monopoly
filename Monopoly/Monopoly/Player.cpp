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
	cleanPlayerLocation();
	location = location->nextBlock;
	drawPlayerLocation();
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
	//cout << "Player 擲出了" << dicePoint1<<"+"<<dicePoint2 << "點" << endl;
	return pair<int, int>(dicePoint1, dicePoint2);
	
}

void Player::moveForwardByStep(int step)
{
	location->startByThisBlock(this);
	for (int i = 1; i <step; i++)
	{
		gotoNextBlock();
		Sleep(100);
		location->throughThisBlock(this);
	}
	gotoNextBlock();
	Sleep(100);
	location->arriveThisBlock(this);
}

void Player::moveToBlock(BaseBlock* block)
{
	location = block;
	location->arriveEvent(this);
}

void Player::cleanPlayerLocation()
{
	Cursor subCursor = Draw::cursor.getSubCursor(location->x, location->y, 2);
	subCursor.add(2, 2).inputPos(index, 0);
	subCursor << "　";
}

void Player::drawPlayerLocation()
{
	Cursor subCursor = Draw::cursor.getSubCursor(location->x, location->y, 2);
	subCursor.add(2, 2).inputPos(index, 0);
	subCursor << Color::F_PLAYER_COLOR[index] << Draw::number[index];
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

void Player::giveMoney(Player * player, int money)
{
	player->earnMoney(money);
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
	//cout <<	"玩家金錢:" << getMoney() <<"   ";
	//cout << "現在位置"<< location->index << endl;
}

void Player::drawPlayerInfo()
{
	Cursor cursor(16, 8);
	for (int i = 0; i <= 17; i++)
	{
		cursor << Draw::infoBlock[i];
		cursor.nextLine();
	}
	cursor.add(3, -1, 12);
	cursor << pair<string, int>(" 玩　家　資　訊 ", 49);
	cursor.add(0, 6);
	cursor << "ＩＤ：" << "1";
	cursor.nextPos();
	cout << "總資金＄" << money + saving;
	cursor.nextLine().nextLine();
	cout << "現金＄" << money;
	cursor.nextPos();
	cout << "存款＄" << saving;
	cursor.nextPos();
	cout << "負債＄" << debit;
	cursor.nextLine().nextLine();
	cout << "持有股票：" << "抬機店x5" << "　" << "紅海x10";
	cursor.nextLine().nextLine().nextLine();
	cout << "持有土地：";
	vector<EstateBlock*>::iterator it;
	for (it = ownedEstates.begin(); it != ownedEstates.end(); it++)
	{
		cout << (*it)->name;
		cursor.nextPos();
	}
	cursor.nextLine().nextLine().nextLine();
	cout << "持有道具：" << "▲x5";
}
