#include "Map.h"
#include"BaseBlock.h"




Map::Map(string newMapName):mapName(newMapName)
{
	blockNums = -1;
	blocksHead =NULL;
}

void Map::calcBlocksLocation()
{
	calcBlockNums();
	BaseBlock* hold = blocksHead;
	while (hold->nextBlock != blocksHead)
	{
		
		hold->setLocationXY(blockNums);
		hold->output();
		hold = hold->nextBlock;
	}hold->setLocationXY(blockNums); hold->output();
}

void Map::insertBlock( BaseBlock* b)
{
	if (blocksHead==NULL)
	{
		blocksHead = b;
		b->nextBlock = blocksHead;
		return;
	}
	BaseBlock* hold = blocksHead;

	while (hold->nextBlock!= blocksHead)
	{
		hold = hold->nextBlock;
	}
	hold->nextBlock = b;
	b->nextBlock = blocksHead;
	
}

BaseBlock* Map::findBlock(int index)
{
	BaseBlock* hold = blocksHead;
	for (size_t i = 0; i < index; i++)
	{
		hold = hold->nextBlock;
	}
	return hold;
}

void Map::calcBlockNums()
{
	int count = 1;
	BaseBlock* hold = blocksHead;
	while (hold->nextBlock != blocksHead)
	{
		
		hold = hold->nextBlock;
		count++;
	}
	blockNums = count;
}


Map::~Map()
{
}