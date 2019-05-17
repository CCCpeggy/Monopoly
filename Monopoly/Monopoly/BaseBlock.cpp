#include "BaseBlock.h"
#include "Player.h"
#include<iostream>
using namespace std;

BaseBlock::BaseBlock(string newName,int newIndex):name(newName),index(newIndex)
{
	x = 0;
	y = 0;
}

BaseBlock::BaseBlock()
{
	name = "newName";
	index = 0;
	x = 0;
	y = 0;
}

BaseBlock& BaseBlock::operator=(const BaseBlock& b)
{
	this->name = b.name;
	this->index = b.index;
	this->x = b.x;
	this->y = b.y;
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
