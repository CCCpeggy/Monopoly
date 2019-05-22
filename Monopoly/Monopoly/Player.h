#pragma once
#include <vector>
#include <map>
#include <windows.h>
#include "Draw.h"
#define POSITION(x,y)  pair<int, int>(0+(x)*10,0+(y)*4)
using namespace std;
class BaseBlock;
class EstateBlock;
class Stock;
class Player
{
public:
	string name;
	vector<EstateBlock*> ownedEstates;
	//vector<Item>;
	BaseBlock* location;
	int getMoney();//return money
	int getDebit();//return debit
	int getSaving();//return saving
	void rollDice(int blockNums);
	void tradeStock(Stock*,bool buyTrueSellFalse,int);
	void earnMoney(int);//ах©З
	void giveMoney(Player&, int);
	void buyHouse(EstateBlock&);
	void outputInformation();
	void displayPlayerLocation();
	Player(string newName="playerName",int newMoney=0,int newDebit=0,int newSaving=0,BaseBlock* newLocation=NULL);
	~Player();

	void gotoNextBlock(int blockNums);
private:
	void arriveBlock();
	int money;
	int debit;
	int saving;
};

