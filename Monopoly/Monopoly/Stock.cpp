#include "Stock.h"
#include "Player.h"


Stock::Stock(string newName, double newPrize, vector<Player*> players):index(newName),prize(newPrize)
{
	for (Player* player:players)
	{
		beOwned.insert(pair<Player*, int>(player,0));
	}
}

Stock::Stock(vector<Player*> players) : index("stock"), prize(20)
{
	for (Player* player : players)
	{
		beOwned.insert(pair<Player*, int>(player, 0));
	}
}

void Stock::fluctuate()
{
	srand(time(NULL));
	double fluctuateRate = (rand() % 11-5)*0.01;
	prize += fluctuateRate * prize;
}


Stock::~Stock()
{
}
