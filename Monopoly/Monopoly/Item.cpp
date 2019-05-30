#include "Item.h"
#include "BaseBlock.h"
#include "Player.h"
/*
Item Item::itemList[] = { 
	Item("路障", "放置到指定格子上，使經過的玩家停止。",&Game::setStopItem)
	,Item("遙控骰子", "自由選擇前進的點數(2~12)",&Game::setAbleChooseDice)
};*/

Item Item::itemList[2] = { 
	Item("路障", "放置到指定格子上，使經過的玩家停止。",&Game::setStopItem)
	,Item("遙控骰子", "自由選擇前進的點數(2~12)",&Game::setAbleChooseDice)
};


void Item::doFunction(Game * game)
{
	(game->*function)();
}

Item::Item(std::string newName, std::string newContent, void(Game::* newFunction)(void)):name(newName),content(newContent)
{
	//newFunction = function;
	string tmp;
}

void Item::operator=(const Item& item)
{
	name = item.name;
	content = item.content;
	//function = item.function;
}

Item::Item(const Item& item):name(item.name), content(item.content)
{
}

Item::Item()
{
}


Item::~Item()
{
}
