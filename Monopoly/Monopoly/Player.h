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
	//���
	Cursor cursor;
	int index;
	vector<EstateBlock*> ownedEstates;
	vector<Item*> ownedItems;//remember to pop after use
	map<Stock*, int> ownedStocks;
	BaseBlock* location;
	static const string playerID[];

	//������
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

	//����ާ@
	public:
		void moveForwardByStep(int step);
		void moveToBlock(BaseBlock*);
	private:
		void gotoNextBlock();

	//���y�ާ@
	public:
		void tradeStock(Stock*,bool buyTrueSellFalse,int);
		void earnMoney(int);//�ȿ�
		void loseMoney(int);//���h����
		void giveMoney(Player * , int);
		void setBankrupt();
		void deposit(int);//�s�� �{��->�s��
		void withdraw(int);//���� �s��->�{��
		void loan(int);//�U��
		void returnLoan(int);//�ٶU��
		void initEachStock(Stock*, int);
	private:
		void changeSaving(int);//�s���ܰ�
		void changeDebit(int);//�t�ŭ��ܰ�

	//�Цa���ާ@
	public:
		void sellEstate(EstateBlock*);
		void buyHouse(EstateBlock* estate);

	//�D��ާ@
	void useItem(int itemIndex);
	void addItem(int itemIndex);

	//ø�s
	void cleanPlayerLocation();
	void drawPlayerLocation();
	void drawPlayerInfo();
	void drawPlayerAllMoney();
	void drawPlayerAllEstate();
	void drawPlayerMoneyStatus();
	void drawStatusPlayerName();
	void drawPlayerStock();
	//�غc
	private:
		void initStocks(vector<Stock>* stocks);
	public:
		Player(int newIndex = 0, int newMoney = 0, int newDebit = 0, int newSaving = 0, BaseBlock* newLocation = NULL, vector<Stock>* stocks=NULL);

	//�Ѻc
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