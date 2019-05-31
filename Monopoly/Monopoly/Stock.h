#ifndef _STOCK_
#define _STOCK_
#include<iostream>
#include<map>
#include<vector>
using namespace std;
class Player;
class Stock
{
public:
	map<Player*, int> beOwned;
	string name;
	int prize;
	Stock(string newName, double newPrize, vector<Player*> players);
	Stock(vector<Player*> players);
	void fluctuate(); 
	string getName();
	~Stock();
};
#endif // !_STOCK_
