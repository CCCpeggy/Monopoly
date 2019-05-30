#include "Item.h"
#include "BaseBlock.h"
#include "Player.h"
/*
Item Item::itemList[] = { 
	Item("����", "��m����w��l�W�A�ϸg�L�����a����C",&Game::setStopItem)
	,Item("������l", "�ۥѿ�ܫe�i���I��(2~12)",&Game::setAbleChooseDice)
};*/

Item Item::itemList[2] = { 
	Item("����", "��m����w��l�W�A�ϸg�L�����a����C",&Game::setStopItem)
	,Item("������l", "�ۥѿ�ܫe�i���I��(2~12)",&Game::setAbleChooseDice)
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
