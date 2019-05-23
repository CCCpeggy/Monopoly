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
	void drawfullgame();
	static void drawMap();
	void drawupstatus();
	void clearCenter();
};

