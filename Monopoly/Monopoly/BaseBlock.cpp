#include "BaseBlock.h"
#include "Player.h"
#include<iostream>
using namespace std;

BaseBlock::BaseBlock(string newName,int newIndex):name(newName),index(newIndex),nextBlock(NULL)
{
	x = 0;
	y = 0;
}

BaseBlock::BaseBlock() :name("BlockName"), index(0), nextBlock(NULL)
{
	x = 0;
	y = 0;
}

BaseBlock& BaseBlock::operator=(const BaseBlock& block)
{
	this->name = block.name;
	this->index = block.index;
	this->x = block.x;
	this->y = block.y;
	return *this;
}



BaseBlock::~BaseBlock()
{
}

void BaseBlock::setLocationXY(int blockNums)
{
	//if (blockNums%4==0)
	
		int n = blockNums / 4;
		if (index<n)
		{
			y = 0;
			x = index;
		}
		else if(index<2*n)
		{
			y = index - (n );
			x = n;
		}
		else if (index<3*n)
		{
			y = n;
			x = 3 * n - index;
		}
		else if (index < 4* n)
		{
			y = 4 * n - index;
			x = 0;
		}
	
}

void BaseBlock::output()
{
	cout << "name=" << name << ",index =" << index << ",x=" << x << ",y=" << y << endl;
}


void BaseBlock::drawLocationName()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	pair<int, int> pos = POSITION(x, y);
	COORD initPos;
	string tempName=name;
	if (name.length() >=9)
	{
		tempName.erase(8, tempName.length() - 8);
	}
	initPos.X = pos.first +(9-tempName.length())/2+2;
	initPos.Y =pos.second+1 ;
	SetConsoleCursorPosition(hOut, initPos);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::DEF_COLOR);
	cout << tempName;
}