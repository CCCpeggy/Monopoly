#include "Stock.h"
#include "Player.h"
#include "Draw.h"

Stock::Stock(string newName, double newPrize):name(newName),prize(newPrize)
{
}

Stock::Stock() : name("stock"), prize(20)
{
}

void Stock::fluctuate()
{
	srand(time(NULL));
	double fluctuateRate = (rand() % 21-10)*0.01;
	prize += fluctuateRate * prize;
}

string Stock::getName() 
{
	return name;
}

Stock::~Stock()
{
}

void Stock::drawStockFluctuate(int index)
{
	
}