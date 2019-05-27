#pragma once
#include "BaseBlock.h"
#include "Game.h"
#include <string>
using namespace std;
class Player;
class BankBlock :
	public BaseBlock
{
private:
	Game* game;
public:
	void startEvent(Player*);
	void arriveEvent(Player*);
	void throughEvent(Player*);
	BankBlock& operator = (const BankBlock&);
	BankBlock(string newName = "»È¦æ", int newIndex = 14, Game* game = nullptr);
	BankBlock();
	~BankBlock();
};

