#pragma once
#include <vector>
using namespace std;
class BaseBlock;
class EstateBlock;
class Player
{
public:
	vector<EstateBlock*> ownEstates;
	//vector<Item>;
	BaseBlock* location;
	int getMoney();//return money
	int getDebit();//return debit
	int getSaving();//return saving
	void rollDice(int blockNums);
	void earnMoney(int);//ах©З
	void giveMoney(Player&, int);
	void buyHouse(EstateBlock&);
	void outputInformation();
	Player(int newMoney=0,int newDebit=0,int newSaving=0,BaseBlock* newLocation=NULL);
	~Player();

	void gotoNextBlock(int blockNums);
private:
	void arriveBlock();
	int money;
	int debit;
	int saving;
};

