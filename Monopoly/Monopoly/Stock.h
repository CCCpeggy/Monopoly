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
	int lastChanged;
	string name;
	int prize;
	Stock(string newName, double newPrize);
	Stock();
	int fluctuate(); 
	string getName();
	~Stock();
};
#endif // !_STOCK_
