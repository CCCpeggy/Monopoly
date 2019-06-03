#include "Player.h"
#include "BaseBlock.h"
#include "EstateBlock.h"
#include "Stock.h"
#include "Game.h"
#include "Item.h"
#include <time.h>
#include<iostream>
using namespace std;
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

int Player::getEstateValue()
{
	int value = 0;
	vector<EstateBlock*>::iterator iter = ownedEstates.begin();
	for (; iter != ownedEstates.end(); iter++) {
		value += (*iter)->initialPrice / 2;
	}
	return value;
}

int Player::getAsset()
{
	return money - debit + saving + getStocksValue() + getEstateValue();
}

pair<int, int> Player::rollDice()
{
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
		if (!location->getHasRoadBlock())
		{
			location->throughThisBlock(this);
		}
		else
		{	//路障觸發
			location->setRoadBlock(false);
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

void Player::initStocks(vector<Stock>* stocks)
{
	if (stocks==NULL)
	{
		return;
	}
	for (Stock stock:(*stocks))
	{
		ownedStocks.insert(make_pair(&stock, 0));
	}
}

Player::Player(int newIndex, int newMoney, int newDebit, int newSaving, BaseBlock* newLocation, bool isBankrupt, Game* game)
	:index(newIndex), money(newMoney), debit(newDebit), saving(newSaving), location(newLocation), isBankrupt(isBankrupt), game(game)
{
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
	drawPlayerMoneyStatus();
}

void Player::loseMoney(int money)
{
	this->money -= money;
	drawPlayerMoneyStatus();
}

void Player::giveMoney(Player * player, int money)
{
	player->earnMoney(money);
	this->money -= money;
	drawPlayerMoneyStatus();
}

void Player::useItem(int itemIndex)
{
	if (ownedItems[itemIndex]==&Item::itemList[0])
	{
		BaseBlock* b = game->showChoosingMapMode("請選擇格子");
		if (b != nullptr) {
			b->setRoadBlock(true);
			ownedItems.erase(ownedItems.begin() + itemIndex);
		}
	}
	else if (ownedItems[itemIndex] == &Item::itemList[1])
	{
		controlDiceNum = Game::showNumberDialog("請選擇要前進的格數", 2, 12, 2, 1, "步");
		if (controlDiceNum != 沒有選擇) {
			moveForwardByStep(controlDiceNum);
			ownedItems.erase(ownedItems.begin() + itemIndex);
		}
	}
}

void Player::addItem(int itemIndex)
{
	ownedItems.push_back(&Item::itemList[itemIndex]);
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
	drawPlayerMoneyStatus();

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
	drawPlayerMoneyStatus();
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
	drawPlayerMoneyStatus();
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

void Player::initEachStock(Stock* stockIndex, int quantity)
{
	ownedStocks[stockIndex] = quantity;
}

void Player::changeDebit(int n)
{
	debit += n;
	drawPlayerMoneyStatus();

}

string Player::getName()
{
	return name;
}

void Player::drawPlayerInfo()
{
	Cursor cursor = Draw::dialogCursor.getSubCursor(5, 7, 12);
	cursor << "ＩＤ："<<index+1 ;
	cursor.nextLine().nextLine();
	cout << "總資金＄" << getAsset();
	cursor.nextLine().nextLine();
	cout << "現金＄" << money;
	cursor.nextPos();
	cout << "存款＄" << saving;
	cursor.nextPos();
	cout << "負債＄" << debit;
	cursor.nextLine().nextLine();
	cout << "地產總數：";
	cout << ownedEstates.size();
	cursor.nextLine().nextLine();
}

void Player::drawPlayerAllMoney()
{
	Cursor cursor = Draw::dialogCursor.getSubCursor(20, 6, 4, 2);
	cursor.nextLine();
	cursor <<"總資產＄"<<getAsset();
	cursor.nextLine();
	cursor << "存款＄"<<getSaving();
	cursor.nextLine();
	cursor << "現金＄" << getMoney();
	cursor.nextLine();
	cursor << "負債＄" << getDebit();
}

void Player::drawPlayerAllEstate()
{
	vector<EstateBlock*>::iterator it;
	Cursor cursor = Draw::dialogCursor.getSubCursor(4, 6, 15, 2);
	for (int i = 0; i < 3; i++) {
		cursor << pair<string, int>(Draw::playerEstateInfoTitle[i], 15);
		cursor.nextPos();
	}
	cursor.nextLine();
	for (it = ownedEstates.begin(); it != ownedEstates.end(); it++)
	{    
			cursor << pair<string,int>((*it)->name,15);
			cursor.nextPos();
			cursor << pair<string, int>(to_string((*it)->houseLevel),15);
			cursor.nextPos();
			cursor << pair<string, int>(to_string((*it)->currentTolls()), 15);
			cursor.nextLine();
	}
}

void Player::drawPlayerMoneyStatus()
{
	Cursor cursor = Draw::playerStatusCursor.getSubCursor(10, 2, 18).getSubCursor(index, 0, 1, 1 );
	for (int i = 0; i < 3; i++) {
		cursor << "           ";
		cursor.nextLine();
	}
	cursor.inputPos(0, 0);
	if (isBankrupt)
		cursor << "破產";
	else {
		cursor << money;
		cursor.nextLine();
		cursor << debit;
		cursor.nextLine();
		cursor << saving;
	}
}

void Player::drawStatusPlayerName()
{
	Cursor cursor = Draw::playerStatusCursor.getSubCursor(10, 1, 18);
	cursor.inputPos(index);
	cursor << Color::B_PLAYER_COLOR[index] << left << setw(16) << name << Color::DEF_COLOR;
}

void Player::drawPlayerStock(int stockIndex)
{
	map<Stock*,int>::iterator it;
	vector<pair<Stock*, int>> temp;
	vector<pair<Stock*, int>>::iterator itt;
	Cursor cursor = Draw::dialogCursor.getSubCursor(4, 6, 15, 2);
	for (int i = 0; i < 3; i++) 
	{
		cursor << pair<string, int>(Draw::playerStockInfoTitle[i], 15);
		cursor.nextPos();
	}
	cursor.nextLine();
	for (it = ownedStocks.begin(); it != ownedStocks.end(); it++)
	{
		temp.push_back(pair<Stock*, int>((*it).first, (*it).second));
	}
	int k = 0;
	int page = stockIndex / 5;
	if (temp.size() >= page * 5)
	{
		itt = temp.begin() + page * 5;
	}
	while(itt != temp.end()&&k<5)
	{
		if ((*itt).second != 0)
		{
			if (stockIndex % 5 == k)
			{
				cursor << Color::TAG_CHOOSE_COLOR << "　　　　　　　　　　　　　　　　　　　　　　";
				cursor << pair<string, int>((*itt).first->getName(), 15);
				cursor.nextPos();
				cursor <<  pair<string, int>(to_string((*itt).second), 15);
				cursor.nextPos();
				cursor << pair<string, int>(to_string((*itt).first->prize), 15);
				cursor.nextLine();
			}
			else
			{
				cursor << Color::DEF_COLOR<<pair<string, int>((*itt).first->getName(), 15);
				cursor.nextPos();
				cursor << Color::DEF_COLOR<<pair<string, int>(to_string((*itt).second), 15);
				cursor.nextPos();
				cursor << Color::DEF_COLOR<<pair<string, int>(to_string((*itt).first->prize), 15);
				cursor.nextLine();
			}
		}
		k++;
		itt++;
	}

}

void Player::drawPlayerItem()
{
	Cursor cursor = Draw::dialogCursor.getSubCursor(4, 6, 45, 2);
	vector<Item*>::iterator it;
	int itemCount[] = { 0 };
	cursor.nextLine();
	for (it = ownedItems.begin(); it != ownedItems.end(); it++)
	{
		cursor << pair<string,int>((*it)->name,45);
		cursor.nextLine();
	}

}