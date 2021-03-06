#ifndef _BaseBlock_
#define _BaseBlock_ 
#include <string>
#include <windows.h>
#include <iostream>
#include <utility>
#include "Draw.h"
#include "Player.h"
using namespace std;
class BaseBlock
{
public:
	string name;
	int x;
	int y;
	int index;
	BaseBlock* nextBlock;
	BaseBlock(string newName,int index);
	BaseBlock();
	BaseBlock& operator = (const BaseBlock&);
	~BaseBlock();
	virtual int getCategory();
	void startByThisBlock(Player*);
	void arriveThisBlock(Player*);
	void throughThisBlock(Player*); 
	virtual void  startEvent(Player*) {};
	virtual void  arriveEvent(Player*) {};
	virtual void  throughEvent(Player*) {};
	void setLocationXY(int blockNums);
	void output();
	virtual void drawBlockInfo();
	virtual void drawLocationName();
	virtual void drawSelected();
	virtual void cleanSelected();
	void drawItem();
	void setRoadBlock(bool);
	bool getHasRoadBlock();
	virtual void drawBlockInfoCenter() {};
private:

	bool hasRoadBlock;
};
#endif // !_BaseBlock_


