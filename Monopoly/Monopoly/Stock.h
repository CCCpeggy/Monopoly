#pragma once
#include<iostream>
#include<map>
#include<vector>
using namespace std;
class Player;
class Stock
{
public:
	map<Player*, int> beOwned;
	string index;
	double prize;
	Stock(string newName, double newPrize, vector<Player*> players);
	Stock(vector<Player*> players);
	void fluctuate(); 
	~Stock();
};

