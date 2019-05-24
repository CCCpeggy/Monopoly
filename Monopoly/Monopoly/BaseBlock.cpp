#include "BaseBlock.h"
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

void BaseBlock::startByThisBlock(Player* player)
{
	startEvent(player);
}

void BaseBlock::arriveThisBlock(Player* player)
{
	throughEvent(player);
	arriveEvent(player);
}

bool BaseBlock::throughThisBlock(Player* player)
{
	
	if (false)//¦³¸ô»Ù
	{
		return false;
	}
	throughEvent(player);
	return true;
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
	Cursor subCursor = Draw::cursor.getSubCursor(x, y, 2);
	subCursor.add(2, 1);
	subCursor << pair<string, int>(name.substr(0,9), 9);
}