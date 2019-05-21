#pragma once
#include<vector>
#include<string>
#include "BaseBlock.h"
using namespace std;
class Player;
class EstateBlock :public BaseBlock
{
public:
	int houseLevel;//-1=no house  0 1 2 3 
	int initialPrice;
	Player* owner;
	int* tolls=new int[4];
	void arrive(Player*);
	void through(Player*);

	EstateBlock& operator=( EstateBlock&);
	EstateBlock(int newIndex,string newName, int newInitialPrice, int* newTolls , Player* owner = NULL, int houseLevel = -1);
	EstateBlock();
	~EstateBlock();
};

