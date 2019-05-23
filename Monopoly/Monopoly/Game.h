#include"Draw.h"
#include "Player.h"
#include "BaseBlock.h"
#include "Map.h"
#include "EstateBlock.h"
#include "StartBlock.h"
#include "FateBlock.h"
#include "ChanceBlock.h"
#include<vector>
#include<string>
#include<iomanip>
#include <windows.h>
#include <utility>

#define LAND 0
#define CHANCE 1
#define FATE 2

class Game
{
private:
	Map map;
	vector<Player> player;
public:
	Game();
	static void drawMap();
	void drawLocationName(vector<string>LocationNameList, vector<EstateBlock*>owner);
	void drawupstatus();
	void drawDialogue(int mode);
};

