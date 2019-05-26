#ifndef _CHANCEBLOCK_
#define _CHANCEBLOCK_
#include<vector>
#include<string>
#include "BaseBlock.h"
#include "Game.h"
using namespace std;
class Player;
class Card;
class ChanceBlock :
	public BaseBlock
{
public:
	vector<Card> chanceCards;
	ChanceBlock& operator=(ChanceBlock&);
	void startEvent(Player*);
	void arriveEvent(Player*);
	void throughEvent(Player*);
	ChanceBlock(int newIndex, string newName);
	ChanceBlock();
	static const string card[];
	~ChanceBlock();
};

#endif // !_CHANCEBLOCK_