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
	if (controlDiceNum > 0)//������l
	{
		dicePoint1 = controlDiceNum / 2;
		dicePoint2 = controlDiceNum - dicePoint1;
		controlDiceNum = 0;
	}
	
	//cout << "Player �Y�X�F" << dicePoint1<<"+"<<dicePoint2 << "�I" << endl;
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
		{	//����Ĳ�o
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
	subCursor << "�@";
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
		BaseBlock* b = game->showChoosingMapMode("�п�ܮ�l");
		if (b != nullptr) {
			b->setRoadBlock(true);
			ownedItems.erase(ownedItems.begin() + itemIndex);
		}
	}
	else if (ownedItems[itemIndex] == &Item::itemList[1])
	{
		controlDiceNum = Game::showNumberDialog("�п�ܭn�e�i�����", 2, 12, 2, 1, "�B");
		if (controlDiceNum != �S�����) {
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
			//cout<<"��X�Цa��:"<<estate->name<<endl;
			return;
		}
	}
}

void Player::buyHouse(EstateBlock * estate)
{
	
	if (estate->houseLevel==-1)
	{
		ownedEstates.push_back(estate);
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
	//cout <<	"���a����:" << getMoney() <<"   ";
	//cout << "�{�b��m"<< location->index << endl;
}

bool Player::getIsBroken()
{
	return isBankrupt;
}

void Player::setBankrupt()
{
	cleanPlayerLocation();
	stringstream ss;
	ss << name << "�}��";
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

void Player::drawPlayerInfo(bool choosed)
{
	vector<string> output;
	output.push_back("�עҡG" + to_string(index + 1));
	output.push_back("�`����G�C" + to_string(getAsset()));
	output.push_back("�{���G�C" + to_string(money));
	output.push_back("�s�ڡG�C" + to_string(saving));
	output.push_back("�t�šG�C" + to_string(debit));
	output.push_back("�a���`�ơG" + to_string(ownedEstates.size()));
	Game::showPlayerInfo(output, choosed);
}

void Player::drawPlayerAllMoney(bool choosed)
{
	vector<string> output;
	output.push_back("�`����G�C" + to_string(getAsset()));
	output.push_back("�{���G�C" + to_string(money));
	output.push_back("�s�ڡG�C" + to_string(saving));
	output.push_back("�t�šG�C" + to_string(debit));
	output.push_back("�в��`�B�G�C" + to_string(getEstateValue()));
	output.push_back("�Ѳ��`�B�G�C" + to_string(getStocksValue()));
	Game::showPlayerInfo(output, choosed);
}

void Player::drawPlayerAllEstate(bool choosed)
{
	vector<EstateBlock*>::iterator it;
	vector<string>titleName;
	for (int i = 0; i < 3; i++) {
		titleName.push_back(Draw::playerEstateInfoTitle[i]);
	}
	vector<vector<string> > output;
	for (it = ownedEstates.begin(); it != ownedEstates.end(); it++)
	{
		vector<string> a(3);
		a[0] = (*it)->name;
		a[1] = to_string((*it)->houseLevel);
		a[2] = to_string((*it)->currentTolls());
		output.push_back(a);
	}
	Game::showPlayerInfo("", titleName, output, 3, 0, 2, choosed);
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
		cursor << "�}��";
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

void Player::drawPlayerStock(bool choosed)
{
	map<Stock*,int>::iterator it;
	vector<pair<Stock*, int>> temp;
	vector<pair<Stock*, int>>::iterator itt;
	vector<string>title;
	vector<vector<string> > content;
	for (int i = 0; i < 3; i++) 
	{
		title.push_back(Draw::playerStockInfoTitle[i]);
	}
	for (it = ownedStocks.begin(); it != ownedStocks.end(); it++)
	{
		if ((*it).second != 0)
		{
			vector<string> a (3);
			a[0] = (*it).first->getName();
			a[1] = to_string((*it).second);
			a[2] = to_string((*it).first->prize);
			content.push_back(a);
		}
	}
	Game::showPlayerInfo("", title, content, 3, 0, 2);
}

void Player::drawPlayerItem(bool choosed)
{
	Cursor cursor = Draw::dialogCursor.getSubCursor(4, 6, 22, 2);
	vector<Item*>::iterator it;
	int itemCount[] = {0,0};
	vector<string>colName;
	for (int i = 0; i < 2; i++)
	{
		colName.push_back(Draw::playerItemTitle[i]);
	}
	cursor.nextLine();
	for (it = ownedItems.begin(); it != ownedItems.end(); it++)
	{
		if (strcmp(Draw::itemName[0].c_str(), (*it)->name.c_str()) == 0)
		{
			itemCount[0]++;
		}
		else if (strcmp(Draw::itemName[1].c_str(), (*it)->name.c_str()) == 0)
		{
			itemCount[1]++;
		}
	}
	vector<vector<string> > words;
	for (int i = 0; i < 2; i++)
	{
		if (itemCount[i] != 0)
		{
			vector<string> a(2);
			a[0] = Draw::itemName[i];
			a[1] = to_string(itemCount[i]);
			words.push_back(a);
		}
	}
	
	Game::showPlayerInfo("", colName, words, 2, 0, 1, choosed);
}