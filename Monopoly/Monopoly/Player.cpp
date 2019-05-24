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
	//cout << "Player �Y�X�F" << dicePoint1<<"+"<<dicePoint2 << "�I" << endl;
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
	//cout <<	"���a����:" << getMoney() <<"   ";
	//cout << "�{�b��m"<< location->index << endl;
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
	cursor << pair<string, int>(" ���@�a�@��@�T ", 49);
	cursor.add(0, 6);
	cursor << "�עҡG" << "1";
	cursor.nextPos();
	cout << "�`����C" << money + saving;
	cursor.nextLine().nextLine();
	cout << "�{���C" << money;
	cursor.nextPos();
	cout << "�s�ڢC" << saving;
	cursor.nextPos();
	cout << "�t�ŢC" << debit;
	cursor.nextLine().nextLine();
	cout << "�����Ѳ��G" << "�����x5" << "�@" << "����x10";
	cursor.nextLine().nextLine().nextLine();
	cout << "�����g�a�G";
	vector<EstateBlock*>::iterator it;
	for (it = ownedEstates.begin(); it != ownedEstates.end(); it++)
	{
		cout << (*it)->name;
		cursor.nextPos();
	}
	cursor.nextLine().nextLine().nextLine();
	cout << "�����D��G" << "��x5";
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