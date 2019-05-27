#include "Player.h"
#include "BaseBlock.h"
#include "EstateBlock.h"
#include "Stock.h"
#include "Game.h"
#include "Item.h"
#include <time.h>
#include<iostream>
using namespace std;
const string Player::playerID[] = { "１","２","３","４" };
void Player::gotoNextBlock()
{
	cleanPlayerLocation();
	location = location->nextBlock;
	drawPlayerLocation();
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

int Player::getStocksValue()
{
	int sum = 0;
	for (auto stock:ownedStocks)
	{
		sum += stock.first->prize * stock.second;
	}
	return sum;
}

pair<int, int> Player::rollDice()
{
	srand(time(NULL));
	int dicePoint1 = rand() % 6 + 1;
	int dicePoint2 = rand() % 6 + 1;
	if (controlDiceNum > 0)//遙控骰子
	{
		dicePoint1 = controlDiceNum / 2;
		dicePoint2 = controlDiceNum - dicePoint1;
		controlDiceNum = 0;
	}
	
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
		if (!location->hasRoadBlock)
		{
			location->throughThisBlock(this);
		}
		else
		{	//路障觸發
			location->hasRoadBlock = false;
			location->arriveThisBlock(this);
			return;
		}
	}
	gotoNextBlock();
	Sleep(100);
	location->arriveThisBlock(this);
}

void Player::moveToBlock(BaseBlock* block)
{
	location = block;
	location->arriveThisBlock(this);
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

void Player::initStocks(vector<Stock>& stocks)
{
	for (Stock stock:stocks)
	{
		ownedStocks.insert(make_pair(&stock, 0));
	}
}

Player::Player(int newIndex, int newMoney, int newDebit, int newSaving, BaseBlock* newLocation) :index(newIndex), money(newMoney), debit(newDebit), saving(newSaving), location(newLocation), isBankrupt(false)
{
	ownedItems.push_back(&Item::itemList[0]);	
	ownedItems.push_back(&Item::itemList[1]);
	controlDiceNum =  0;
	stringstream ss;
	ss << "player" << index + 1;
	name = ss.str();
}


Player::~Player()
{
}

void Player::tradeStock(Stock* stock, bool buyTrueSellFalse, int quantity)
{
	if (buyTrueSellFalse)
	{
		ownedStocks[stock] += quantity;
		changeSaving(-(stock->prize * quantity));
	}
	else
	{
		if (ownedStocks[stock] >= quantity)
		{
			ownedStocks[stock] -= quantity;
			changeSaving(stock->prize * quantity);
		}
	}
	/*if (buyTrueSellFalse)
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
	}*/
}

void Player::earnMoney(int money)
{
	this->money += money;
}

void Player::loseMoney(int money)
{
	this->money -= money;
}

void Player::giveMoney(Player * player, int money)
{
	player->earnMoney(money);
	this->money -= money;
}

void Player::useItem(int itemIndex)
{
	if (ownedItems[itemIndex]==&Item::itemList[0])
	{
		//路障 選擇格子
		//BaseBlock* b = ???;
		//b->hasRoadBlock = true;
	}
	else if (ownedItems[itemIndex] == &Item::itemList[1])
	{
		//遙控骰子  選擇格數
		//controlDiceNum = ???;
	}
	ownedItems.erase(ownedItems.begin() + itemIndex);
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

int Player::getTotalHouse()
{
	vector<EstateBlock*>::iterator it = ownedEstates.begin();
	int total = 0;
	for (; it != ownedEstates.end(); it++)
	{
		if ((*it)->houseLevel != -1)  total += (*it)->houseLevel; 
	}
	return total;
}

void Player::outputInformation()
{
	//cout <<	"玩家金錢:" << getMoney() <<"   ";
	//cout << "現在位置"<< location->index << endl;
}

bool Player::getIsBroken()
{
	return isBankrupt;
}

void Player::setBankrupt()
{
	cleanPlayerLocation();
	stringstream ss;
	ss << name << "破產";
	Game::showDialog(ss.str(), "");
	isBankrupt = true;
	vector<EstateBlock*>::iterator it = ownedEstates.begin();
	for (; it != ownedEstates.end(); it++)
	{
		(*it)->beSelled();
	}
}

void Player::deposit(int n)
{
	loseMoney(n);
	changeSaving(n);
}

void Player::withdraw(int n)
{
	earnMoney(n);
	changeSaving(-n);
}

void Player::changeSaving(int n)
{
	saving += n;
}

void Player::loan(int n)
{
	changeDebit(n);
	earnMoney(n);
}

void Player::returnLoan(int n)
{
	changeDebit(-n);
	loseMoney(n);
}

void Player::changeDebit(int n)
{
	debit += n;
}

string Player::getName()
{
	return name;
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
	cursor << "ＩＤ："<<playerID[index] ;
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
		cout << (*it)->name<<"　";
		cursor.nextPos();
	}
	cursor.nextLine().nextLine().nextLine();
	cout << "持有道具：" << "▲x5";
}

void Player::drawPlayerAllMoney()
{
	Cursor cursor(19,11);
	
}