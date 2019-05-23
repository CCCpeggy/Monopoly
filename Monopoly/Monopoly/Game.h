#include "Draw.h"
#include "Player.h"
#include "BaseBlock.h"
#include "Map.h"
#include "EstateBlock.h"
#include "StartBlock.h"
#include "FateBlock.h"
#include "ChanceBlock.h"
#include "Stock.h""
#include <vector>
#include <string>
#include <iomanip>
#include <windows.h>
#include <utility>
#include <fstream>
#include <sstream>

#define LAND 0
#define CHANCE 1
#define FATE 2
#define LOADFILE "init3.txt"

class Game
{
private:
	Map map;
	vector<Stock> stock;
	vector<Player> player;
	int playerIndex;
	int round;
public:
	Game();
	void loadFile(string);
	static void drawMap();
	void drawupstatus();
};

