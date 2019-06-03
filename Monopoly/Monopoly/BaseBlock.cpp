#include "BaseBlock.h"
BaseBlock::BaseBlock(string newName, int newIndex) :name(newName), index(newIndex), nextBlock(NULL), hasRoadBlock(false)
{
	x = 0;
	y = 0;
}

BaseBlock::BaseBlock() :name("BlockName"), index(0), nextBlock(NULL), hasRoadBlock(false)
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

int BaseBlock::getCategory()
{
	return -3;
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

void BaseBlock::throughThisBlock(Player* player)
{
	throughEvent(player);
}

void BaseBlock::setLocationXY(int blockNums)
{
	//if (blockNums%4==0)
	
	int n = (blockNums+3) / 4;
	n = n < 7 ? 7 : n;
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
	//cout << "name=" << name << ",index =" << index << ",x=" << x << ",y=" << y << endl;
}

void BaseBlock::drawBlockInfo()
{
	drawItem();
}


void BaseBlock::drawLocationName()
{
	Cursor subCursor = Draw::cursor.getSubCursor(x, y, 2);
	subCursor.add(2, 1);
	subCursor << pair<string, int>(name.substr(0,8), 8);
}

void BaseBlock::drawSelected()
{
	Cursor subCursor = Draw::cursor.getSubCursor(x, y, 2);
	subCursor.add(2, 1);
	for (int i = 0; i < 3; i++) {
		subCursor << Color::TAG_CHOOSE_COLOR << "¡@¡@¡@¡@";
		subCursor.nextLine();
	}
}

void BaseBlock::cleanSelected()
{
	Cursor subCursor = Draw::cursor.getSubCursor(x, y, 2);
	subCursor.add(2, 1);
	for (int i = 0; i < 3; i++) {
		subCursor << Color::DEF_COLOR << "¡@¡@¡@¡@";
		subCursor.nextLine();
	}
	drawLocationName();
}

void BaseBlock::drawItem()
{

	Cursor subCursor = Draw::cursor.getSubCursor(x, y, 2);
	subCursor.add(2, 3);
	subCursor << (hasRoadBlock ? "¡¶" : "¡@");
}

void BaseBlock::setRoadBlock(bool has)
{
	hasRoadBlock = has;
	drawItem();
}

bool BaseBlock::getHasRoadBlock()
{
	return hasRoadBlock;
}

void BaseBlock::OutputBlockInfo()
{
	Cursor cursor = Draw::dialogCursor.getSubCursor(5, 7, 12);
	cursor << "¤g¦aÃþ«¬¡G" << name;
}
