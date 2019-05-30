#ifndef _BASEBLOCK_
#define _BASEBLOCK_
#include "BaseBlock.h"
class Player;
class StartBlock :
	public BaseBlock
{
public:
	virtual int getCategory();
	void startEvent(Player*);
	void arriveEvent(Player*);
	void throughEvent(Player*);
	StartBlock& operator = (const StartBlock&);
	StartBlock(string newName = "°_ÂI",int newIndex=0);
	//void drawLocationName();
	~StartBlock();
};
#endif // !_BASEBLOCK_


