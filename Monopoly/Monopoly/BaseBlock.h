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
#endif // !_BaseBlock_


