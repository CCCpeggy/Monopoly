
#include"Player.h"
#include"BaseBlock.h"
#include"Map.h"
#include"EstateBlock.h"
#include"StartBlock.h"
#include<iostream>
using namespace std;
int main() {
	Map map("map1");
	StartBlock* start = new StartBlock("�_�I", 0);
	map.insertBlock(start);
	Player p1(50000, 0, 0, map.findBlock(0));
	for (size_t i = 1; i < 28; i++)
	{

		int* toll = new int[4]{ 100,200,300,400 };
		EstateBlock* s = new EstateBlock(i, "EstateBlock", 2000, toll);
		map.insertBlock(s);
	}
	map.calcBlocksLocation();


	int a;
	while (cin >> a)
	{
		p1.rollDice(map.blockNums);
	}
	system("PAUSE");
}