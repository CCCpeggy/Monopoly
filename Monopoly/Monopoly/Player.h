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
class Item;
class Player
{
public:
	//資料
	Cursor cursor;
	int index;
	vector<EstateBlock*> ownedEstates;
	vector<Item*> ownedItems;//remember to pop after use
	map<Stock*, int> ownedStocks;
	BaseBlock* location;
	static const string playerID[];

	//獲取資料
	int getMoney();//return money
	int getDebit();//return debit
	int getSaving();//return saving
	int getStocksValue();
	int getEstateValue();
	int getAsset();
	pair<int,int> rollDice();
	int getTotalHouse();
	void outputInformation();
	bool getIsBroken();
	string getName();

	//角色操作
	public:
		void moveForwardByStep(int step);
		void moveToBlock(BaseBlock*);
	private:
		void gotoNextBlock();

	//金流操作
	public:
		void tradeStock(Stock*,bool buyTrueSellFalse,int);
		void earnMoney(int);//賺錢
		void loseMoney(int);//失去金錢
		void giveMoney(Player * , int);
		void setBankrupt();
		void deposit(int);//存錢 現金->存款
		void withdraw(int);//提款 存款->現金
		void loan(int);//貸款
		void returnLoan(int);//還貸款
		void initEachStock(Stock*, int);
	private:
		void changeSaving(int);//存款變動
		void changeDebit(int);//負債值變動

	//房地產操作
	public:
		void sellEstate(EstateBlock*);
		void buyHouse(EstateBlock* estate);

	//道具操作
	void useItem(int itemIndex);
	void addItem(int itemIndex);

	//繪製
	void cleanPlayerLocation();
	void drawPlayerLocation();
	void drawPlayerInfo();
	void drawPlayerAllMoney();
	void drawPlayerAllEstate();
	void drawPlayerMoneyStatus();
	void drawStatusPlayerName();
	void drawPlayerStock();
	//建構
	private:
		void initStocks(vector<Stock>* stocks);
	public:
		Player(int newIndex = 0, int newMoney = 0, int newDebit = 0, int newSaving = 0, BaseBlock* newLocation = NULL, vector<Stock>* stocks=NULL);

	//解構
	~Player();


private:
	string name;
	int controlDiceNum;
	int money;
	int debit;
	int saving;
	bool isBankrupt;
};

#endif // !_PLAYER_