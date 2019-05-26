#ifndef _PLAYER_
#define _PLAYER_
#include <vector>
#include <map>
#include <sstream>
#include <windows.h>
#include "Draw.h"
#include "Cursor.h"
using namespace std;
extern HANDLE handleOutput;
class BaseBlock;
class Game;
class EstateBlock;
class Stock;
class Player
{
public:
	Cursor cursor;
	int index;
	vector<EstateBlock*> ownedEstates;
	//vector<Item>;
	BaseBlock* location;
	int getMoney();//return money
	int getDebit();//return debit
	int getSaving();//return saving
	pair<int,int> rollDice();
	void moveForwardByStep(int step);
	void moveToBlock(BaseBlock*);
	void tradeStock(Stock*,bool buyTrueSellFalse,int);
	void earnMoney(int);//賺錢
	void loseMoney(int);//失去金錢
	void giveMoney(Player * , int);
	void sellEstate(EstateBlock*);
	void buyHouse(EstateBlock * estate);
	int getTotalHouse();
	void outputInformation();
	bool getIsBroken();
	void setBankrupt();
	string getName();
	Player(int newIndex=0,int newMoney=0,int newDebit=0,int newSaving=0,BaseBlock* newLocation=NULL);
	~Player();
	void gotoNextBlock();
	void cleanPlayerLocation();
	void drawPlayerLocation();
	void drawPlayerInfo();
	void drawPlayerAllMoney();
	static const string playerID[];
private:
	void arriveBlock();
	string name;
	int money;
	int debit;
	int saving;
	bool isBankrupt;
};

#endif // !_PLAYER_