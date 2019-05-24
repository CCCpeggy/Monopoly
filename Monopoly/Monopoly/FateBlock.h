#ifndef _FATEBLOCK_
#define _FATEBLOCK_
#include<vector>
#include<string>
#include "BaseBlock.h"
using namespace std;
class Player;
class Card;
class FateBlock :
	public BaseBlock
{
public:
	vector<Card> fateCards;
	FateBlock& operator=(FateBlock&);
	void startEvent(Player*);
	void arriveEvent(Player*);
	void throughEvent(Player*);
	FateBlock(int newIndex, string newName);
	FateBlock();
	~FateBlock();
};
#endif // !_FATEBLOCK_