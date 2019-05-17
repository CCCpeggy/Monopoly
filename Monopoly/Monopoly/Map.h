#pragma once
#include<vector>
#include<string>
using namespace std;
class BaseBlock;
class Map
{
public:
	string mapName;
	BaseBlock* blocksHead;
	int blockNums;
	Map(string newMapName ="MapName");
	void calcBlocksLocation();
	void insertBlock(BaseBlock*);
	BaseBlock* findBlock(int index);
	void calcBlockNums();
	~Map();
};

