#pragma once
#include<string>
#include <windows.h>
#include "Draw.h"
#include <utility>
#define POSITION(x,y)  pair<int, int>(0+(x)*10,0+(y)*4)
using namespace std;
class Player;
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
	void startByThisBlock(Player*);
	void arriveThisBlock(Player*);
	bool throughThisBlock(Player*); 
	virtual void  startEvent(Player*) {};
	virtual void  arriveEvent(Player*) {};
	virtual void  throughEvent(Player*) {};
	//virtual void drawDialogueBoxInfo(string text);
	void setLocationXY(int blockNums);
	void output();
	virtual void drawLocationName();
private:
};


