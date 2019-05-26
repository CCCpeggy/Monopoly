#ifndef _PLAYER_
#define _PLAYER_
#include <vector>
#include <map>
#include <windows.h>
#include "Draw.h"
#include "Cursor.h"
using namespace std;
extern HANDLE handleOutput;
class BaseBlock;
class Game;
class EstateBlock;
class Stock;
class Item;
class Player
{
public:
	Cursor cursor;
	int index;
	vector<EstateBlock*> ownedEstates;
	vector<Item*> ownedItems;//remember to pop after use
	int controlDiceNum;
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
	void useItem(int itemIndex);
	void sellEstate(EstateBlock*);
	void buyHouse(EstateBlock * estate);
	int getTotalHouse();
	void outputInformation();
	void drawPlayerLocation();
	Player(int newIndex=0,int newMoney=0,int newDebit=0,int newSaving=0,BaseBlock* newLocation=NULL);
	~Player();
	void gotoNextBlock();
	void cleanPlayerLocation();
	void drawPlayerInfo();
	void drawPlayerAllMoney();
	static const string playerID[];
private:
	int money;
	int debit;
	int saving;
};

#endif // !_PLAYER_