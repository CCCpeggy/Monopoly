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
#define ALL -1
#define LOADFILE "init2.txt"

class Game
{
private:
	Map map;
	vector<Stock> stock;
	vector<Player> player;
	int playerIndex;
	int round;
public:
	static const int FRIST;
	static const int SECOND;

	Game(string = LOADFILE);
	void loadFile(string);
	void showMap();
	void showAllPlayerStatus(); //ª±®aª¬ºA
	void showPlayerInfo();
	void showPlayerPosition(int = ALL);
	void showBlockContent();
	void showPlayStatus(int);
	void showActionMenu();
	void cleanPlayerPosition(int = ALL);
	void cleanCenter();
	bool showDialog(string, pair<string, string>, bool); 
};

