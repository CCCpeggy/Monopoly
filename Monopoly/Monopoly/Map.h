#ifndef _MAP__
#define _MAP__
#include<vector>
#include<string>
#include "Cursor.h"
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
	BaseBlock* operator[](int index);
	//BaseBlock* findBlock(int index);
	void calcBlockNums();
	~Map();
private:
};
#endif // !_MAP__

