#pragma once
#include "BaseBlock.h"
class Player;
class BankBlock :
	public BaseBlock
{
public:
	void startEvent(Player*);
	void arriveEvent(Player*);
	void throughEvent(Player*);
	BankBlock& operator = (const BankBlock&);
	BankBlock(string newName = "�_�I", int newIndex = 14);
	BankBlock();
	~BankBlock();
};

