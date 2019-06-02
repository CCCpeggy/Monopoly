#include "Stock.h"
#include "Player.h"
#include "Draw.h"

Stock::Stock(string newName, double newPrize):name(newName),prize(newPrize), lastChanged(0)
{
}

Stock::Stock() : name("stock"), prize(20)
{
}

double Stock::fluctuate()
{

	double fluctuateRate = (rand() % 21-10)*0.01;
	lastChanged = ((fluctuateRate - 1) * prize);
	prize += lastChanged;
	return lastChanged;
}

string Stock::getName() 
{
	return name;
}

Stock::~Stock()
{
}