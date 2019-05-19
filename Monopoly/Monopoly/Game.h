#include"Draw.h"
#include<vector>
#include<string>
#include<iomanip>
#include <windows.h>
#define LAND 0
#define CHANCE 1
#define FATE 2
class Game
{
public:
	Game();
	void drawfullgame();
	void drawMap();
	void drawLocationName(vector<string>LocationNameList,vector<int>LocationOwner);
	void drawupstatus();
	void drawDialogue(int mode);
};

