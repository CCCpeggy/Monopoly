#ifndef _FATEBLOCK_
#define _FATEBLOCK_
#include<vector>
#include<string>
#include "BaseBlock.h"
#include "Game.h"
using namespace std;
class Player;
class Card;
class FateBlock :
	public BaseBlock
{
private:
	Game* game;
public:
	virtual int getCategory();
	vector<Card> fateCards;
	FateBlock& operator=(FateBlock&);
	void startEvent(Player*);
	void arriveEvent(Player*);
	void throughEvent(Player*);
	FateBlock(int newIndex, string newName, Game* game);
	FateBlock(Game* game);
	static const string card[];
	~FateBlock();
	virtual void OutputBlockInfo();
};
#endif // !_FATEBLOCK_