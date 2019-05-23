#include"Player.h"
#include"BaseBlock.h"
#include"Map.h"
#include"EstateBlock.h"
#include"StartBlock.h"
#include"FateBlock.h"
#include"ChanceBlock.h"
#include<iostream>
using namespace std;
int main() {
	Map map("map1");
	StartBlock* start = new StartBlock("起點", 0);
	map.insertBlock(start);
	Player p1("player1", 50000, 0, 0, map[0]);
	for (size_t i = 1; i < 28; i++)
	{
		if (i == 14)
		{
			FateBlock* fblock = new FateBlock(i, "FateBlock");
			map.insertBlock(fblock);
		}
		else if (i == 27)
		{
			ChanceBlock* cblock = new ChanceBlock(i, "ChanceBlock");
			map.insertBlock(cblock);
		}
		else
		{
			int* toll = new int[4]{ 100,200,300,400 };
			EstateBlock* s = new EstateBlock(i, "EstateBlock", 2000, toll);
			map.insertBlock(s);
		}
	}
	map.calcBlocksLocation();




	int a;
	while (cin >> a)
	{
		p1.rollDice(map.blockNums);
	}
	system("PAUSE");
}
