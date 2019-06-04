#ifndef _EstateBlock_
#define _EstateBlock_
#include <vector>
#include <string>
#include <sstream>
#include "BaseBlock.h"
#include "Game.h"
using namespace std;
class BaseBlock;
class Player;
class EstateBlock :public BaseBlock
{
public:
	int houseLevel;//-1=no house  0 1 2 3 
	int initialPrice;
	Player* owner;
	int* tolls=new int[4];
	void startEvent(Player*);
	void arriveEvent(Player*);
	void throughEvent(Player*);
	void setEstateInfo(Player*, int);
	void drawLocationName();
	void drawBlockInfo();
	void drawEstateLevel();
	virtual void OutputBlockInfo();
	int beSelled();
	int currentTolls();
	int getLevelTolls(int); 
	virtual int getCategory();
	EstateBlock& operator=( EstateBlock&);
	EstateBlock(int newIndex,string newName, int newInitialPrice, int* newTolls , Player* owner = NULL, int houseLevel = -1);
	EstateBlock();
	~EstateBlock();
};
#endif // !_EstateBlock_
