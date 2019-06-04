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
private:
	Game* game;
public:
	virtual int getCategory();
	vector<Card> chanceCards;
	ChanceBlock& operator=(ChanceBlock&);
	void startEvent(Player*);
	void arriveEvent(Player*);
	void throughEvent(Player*);
	ChanceBlock(int newIndex, string newName, Game* game);
	ChanceBlock(Game *game);
	static const string card[];
	~ChanceBlock();
	virtual void drawBlockInfoCenter();
};

#endif // !_CHANCEBLOCK_