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
	if (blockNums%4==0)
	{
		int n = blockNums / 4;
		if (index<n)
		{
			x = 0;
			y = index;
		}
		else if(index<2*n)
		{
			x = index - (n );
			y = n;
		}
		else if (index<3*n)
		{
			x = n;
			y = 3 * n - index;
		}
		else if (index < 4* n)
		{
			x = 4 * n - index;
			y = 0;
		}
	}
	else
	{

	}
}

void BaseBlock::output()
{
	cout << "name=" << name << ",index =" << index << ",x=" << x << ",y=" << y << endl;
}
