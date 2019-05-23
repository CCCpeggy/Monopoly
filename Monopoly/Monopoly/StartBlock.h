#pragma once
#include "BaseBlock.h"
class Player;
class StartBlock :
	public BaseBlock
{
public:
	 void arrive(Player*);
	 void through(Player*);
	StartBlock& operator = (const StartBlock&);
	StartBlock(string newName = "°_ÂI",int newIndex=0);
	//void drawLocationName();
	~StartBlock();
};

