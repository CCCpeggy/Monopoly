#pragma once
#include<iostream>
#include<vector>
using namespace std;
class Player;
class Item
{
public:
	int index;
	string name;
	string content;
	static vector<Item> itemList; 
	Item(string name, string content,int index);
	Item();
	~Item();
};


