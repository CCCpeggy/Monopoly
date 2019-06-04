#include "Stock.h"
#include "Player.h"
#include "Draw.h"

Stock::Stock(string newName, double newPrize, int lastChanged):name(newName),prize(newPrize), lastChanged(lastChanged)
{
}

Stock::Stock() : name("stock"), prize(20)
{
}

int Stock::fluctuate()
{
	int r = (rand() % 21 - 10);
	double fluctuateRate = r*0.01;//-10%~10%
	lastChanged = (int)((fluctuateRate ) * prize+0.5);
	prize += lastChanged;
	//return pair<int, bool>(lastChanged, r == -10 || r == 10 ? true : false);
	return lastChanged;
}

string Stock::getName() 
{
	return name;
}

Stock::~Stock()
{
}