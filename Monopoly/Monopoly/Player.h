#pragma once
#include <vector>
#include <map>
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
	Player(string newName="playerName",int newMoney=0,int newDebit=0,int newSaving=0,BaseBlock* newLocation=NULL);
	~Player();

	void gotoNextBlock(int blockNums);
private:
	void arriveBlock();
	int money;
	int debit;
	int saving;
};

