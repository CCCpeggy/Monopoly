#include "Stock.h"
#include "Player.h"


Stock::Stock(string newName, double newPrize, vector<Player*> players):name(newName),prize(newPrize)
{
	for (Player* player:players)
	{
		beOwned.insert(pair<Player*, int>(player,0));
	}
}

Stock::Stock(vector<Player*> players) : name("stock"), prize(20)
{
	for (Player* player : players)
	{
		beOwned.insert(pair<Player*, int>(player, 0));
	}
}


Stock::~Stock()
{
}
