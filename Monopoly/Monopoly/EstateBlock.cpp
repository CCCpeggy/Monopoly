#include "EstateBlock.h"
#include "Player.h"
#include <iostream>
void EstateBlock::startEvent(Player*)
{

}
void EstateBlock::arriveEvent(Player* player)
{
	cout << "ARRIVE Estate" << endl;
	output();
	if (this->owner==NULL)
	{
		//詢問是否要買地 return bool
		char buychar;
		cout << "是否要買地(價格:" << initialPrice << ")(Y/N)" << endl;
		cin >> buychar;
		if (buychar == 'Y' || buychar == 'y')
		{
			cout << "購買成功" << endl;
			player->buyHouse(this);
			this->owner = player;
		}
		else
		{
			return;
		}
	}
	else if(this->owner != player)
	{
		player->giveMoney(*owner, tolls[houseLevel]);
	}
	else
	{
		if (houseLevel<=2)
		{
			
			char buychar;
			cout << "是否要蓋房子(價格:" << initialPrice * 0.5 << ")(Y/N)" << endl;
			cin >> buychar;
			if (buychar == 'Y' || buychar == 'y')
			{
				cout << "蓋房成功" << endl;
				player->buyHouse(this);
				this->owner = player;
			}
			else
			{
				return;
			}
		}
	}
}

void EstateBlock::throughEvent(Player* player)
{
	player->outputInformation();
	if (true)//若有路障
	{
		//dosomething
	}
	return;
}

EstateBlock& EstateBlock::operator=( EstateBlock& estate)
{
		BaseBlock::operator=(estate);
		houseLevel = estate.houseLevel;
		initialPrice = estate.initialPrice;
		owner = estate.owner;
		tolls = estate.tolls;
		return *this;
	// TODO: 於此處插入傳回陳述式
}

EstateBlock::EstateBlock(int newIndex,string newName, int newInitialPrice, int* newTolls, Player* newOwner, int newHouseLevel):
	BaseBlock(newName,newIndex),initialPrice(newInitialPrice),tolls(newTolls),owner(newOwner),houseLevel(newHouseLevel)
{
}

EstateBlock::EstateBlock():BaseBlock(),houseLevel(-1),initialPrice(0),owner(NULL)
{
}



EstateBlock::~EstateBlock()
{
}

void EstateBlock::drawLocationName()
{
	Cursor subCursor = Draw::cursor.getSubCursor(x, y, 2);
	subCursor.add(2, 1);
	if (owner != NULL)
	{
		subCursor << Color::B_PLAYER_COLOR[owner->index]<<pair<string, int>(name.substr(0, 9), 9);
	}
	else
	{
		subCursor << pair<string, int>(name.substr(0, 9), 9);
	}
}

int EstateBlock::beSelled()
{
	houseLevel = -1;
	owner = NULL;
	return initialPrice*0.5;
}

/*void EstateBlock::drawDialogueBoxInfo(string text)
{
	DialogueBox();
	string title = "確定要購買　　　　　　嗎？";
	string yesNo = "　　　　是　　　　　　　　　　　　　否　　　　";
	COORD posLand;
	posLand.X = 27;
	posLand.Y = 12;
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, posLand);
	cout << title<< endl;
	COORD posLocationName;
	posLocationName.X = 39+(13-name.length())/2;
	posLocationName.Y = 12;
	COORD posChoice;
	posChoice.X = 17;
	posChoice.Y = 17; 
	SetConsoleCursorPosition(hOut, posChoice);
	cout << yesNo << endl;
}*/