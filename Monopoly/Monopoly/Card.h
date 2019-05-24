#ifndef _CARD_
#define _CARD_
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

#endif // !_CARD_