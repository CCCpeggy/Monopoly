#ifndef _BASEBLOCK_
#define _BASEBLOCK_
#include "BaseBlock.h"
class Player;
class StartBlock :
	public BaseBlock
{
public:
	void startEvent(Player*);
	void arriveEvent(Player*);
	void throughEvent(Player*);
	StartBlock& operator = (const StartBlock&);
	StartBlock(string newName = "�_�I",int newIndex=0);
	//void drawLocationName();
	~StartBlock();
};
#endif // !_BASEBLOCK_


