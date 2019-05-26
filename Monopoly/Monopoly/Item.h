#pragma once
#include<iostream>
#include<vector>
using namespace std;
class Player;
class Item
{
public:
	string name;
	string content;
	static vector<Item> itemList; 
	Item(string name, string content);
	Item();
	~Item();
};


