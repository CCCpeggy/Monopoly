#pragma once
#include<vector>
#include<string>
#include "BaseBlock.h"
using namespace std;
class Player;
class Card;
class ChanceBlock :
	public BaseBlock
{
public:
	vector<Card> chanceCards;
	ChanceBlock& operator=(ChanceBlock&);
	void arrive(Player*);
	void through(Player*);
	ChanceBlock(int newIndex, string newName);
	ChanceBlock();
	~ChanceBlock();
};

