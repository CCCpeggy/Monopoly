#ifndef _Item_
#define _Item_
#include <iostream>
#include <vector>
#include <string>
#include "Game.h"
using namespace std;
class Game;
class Player;
class Item
{
public:
	string name;
	string content;
	static Item itemList[2]; 
	void doFunction(Game*);
	void(Game::* function)(void);
	Item(string name, string content, void(Game::*)(void));
	void operator=(const Item&);
	Item(const Item&);
	Item();
	~Item();
private:
};
#endif // !_Item_