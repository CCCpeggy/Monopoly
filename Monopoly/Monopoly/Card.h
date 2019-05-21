#pragma once
#include<string>
using namespace std;
class Player;
class Card
{
public:
	string title;
	string content;
	void event(Player*);
	Card();
	~Card();
};

