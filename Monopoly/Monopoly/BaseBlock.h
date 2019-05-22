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
	virtual void  arrive(Player*)=0;
	virtual void  through(Player*)=0;
	void setLocationXY(int blockNums);
	void output();
	void drawLocationName();
private:
};


