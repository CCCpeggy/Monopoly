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
	cout << "Player �Y�X�F" << dicePoint1<<"+"<<dicePoint2 << "�I" << endl;
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
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	string displayPlayer[4] = { "��","��","��","��" };

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
			//cout<<"��X�Цa��:"<<estate->name<<endl;
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
	cout <<	"���a����:" << getMoney() <<"   ";
	cout << "�{�b��m"<< location->index << endl;
}

void Player::drawPlayerInfo()
{
	int k = 0;
	HANDLE hOut;
	for (int i = 6; i <= 23; i++)
	{
		COORD pos{ 16,i };
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hOut, pos);
		cout << PlayerInfo::infoBlock[k];
		k++;
	}
	string title = "���@�a�@��@�T�@";
	COORD posTitle{ 17 + (49 - title.length()) / 2,9 };
	SetConsoleCursorPosition(hOut, posTitle);
	cout << title << endl;
	COORD posID{ 19,11 };
	SetConsoleCursorPosition(hOut, posID);
	cout << "�עҡG" << "1";
	COORD posMoney{ 35,11 };
	SetConsoleCursorPosition(hOut, posMoney);
	cout << "�`����C" << money + saving;
	COORD posCash{ 19,13 };
	SetConsoleCursorPosition(hOut, posCash);
	cout << "�{���C" << money;
	COORD posSavings{ 34,13 };
	SetConsoleCursorPosition(hOut, posSavings);
	cout << "�s�ڢC" << saving;
	COORD posDebt{ 49,13 };
	SetConsoleCursorPosition(hOut, posDebt);
	cout << "�t�ŢC" << debit;
	SetConsoleCursorPosition(hOut, posSavings);
	COORD posStock{ 19,15 };
	SetConsoleCursorPosition(hOut, posStock);
	cout << "�����Ѳ��G" << "�����x5" << "�@" << "����x10";
	COORD posLand{ 19,18 };
	SetConsoleCursorPosition(hOut, posLand);
	cout << "�����g�a�G";
	vector<EstateBlock*>::iterator it;
	for (it = ownedEstates.begin(); it != ownedEstates.end(); it++)
	{
		cout << (*it)->name << "�@";
	}
	COORD posItem{ 19,21 };
	SetConsoleCursorPosition(hOut, posItem);
	cout << "�����D��G" << "��x5";
	COORD endPos{ 0,34 };
	SetConsoleCursorPosition(hOut, endPos);
}

void tagOverview(int choose)
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	string tagText = "�@�`���@";
	COORD pos2{ 18,7 };
	if (choose == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::TAG_CHOOSE_COLOR);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::DEF_COLOR);
	}
	SetConsoleCursorPosition(hOut, pos2);
	cout << tagText;
}
void tagMoney(int choose)
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	string tagText = "�@����@";
	COORD pos2{ 28,7 };
	if (choose == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::TAG_CHOOSE_COLOR);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::DEF_COLOR);
	}
	SetConsoleCursorPosition(hOut, pos2);
	cout << tagText;
}
void tagEstate(int choose)
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	string tagText = "�@�a���@";
	COORD pos2{ 38,7 };
	if (choose == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::TAG_CHOOSE_COLOR);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::DEF_COLOR);
	}
	SetConsoleCursorPosition(hOut, pos2);
	cout << tagText;
}
void tagStock(int choose)
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	string tagText = "�@�Ѳ��@";
	COORD pos2{ 48,7 };
	if (choose == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::TAG_CHOOSE_COLOR);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::DEF_COLOR);
	}
	SetConsoleCursorPosition(hOut, pos2);
	cout << tagText;
}
void tagItem(int choose)
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	string tagText = "�@�D��@";
	COORD pos2{ 58,7 };
	if (choose == 1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::TAG_CHOOSE_COLOR);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::DEF_COLOR);
	}
	SetConsoleCursorPosition(hOut, pos2);
	cout << tagText;
}