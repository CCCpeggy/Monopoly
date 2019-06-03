#include "EstateBlock.h"
#include "Player.h"
#include <iostream>
void EstateBlock::startEvent(Player*)
{

}
void EstateBlock::arriveEvent(Player* player)
{
	//cout << "ARRIVE Estate" << endl;
	output();
	if (this->owner==NULL)
	{
		if (player->getMoney()>= initialPrice)
		{
			//詢問是否要買地 return bool
			stringstream ss;
			ss << "是否要買地(價格:" << initialPrice << ")";
			bool result = Game::showDialog(ss.str(), pair<string, string>("是", "否"), Draw::FIRST);
			if (result)
			{
				//cout << "購買成功" << endl;
				player->buyHouse(this);
				this->owner = player;
				drawLocationName();
			}
			else
			{
				return;
			}
		}
		else
		{
			stringstream ss;
			ss << "現金不足(價格:" << initialPrice << ")";
			 Game::showDialog("無法買地", ss.str());
		}
		
	}
	else if(this->owner != player)
	{
		player->giveMoney(owner, currentTolls());
		stringstream ss;
		ss << "支付 "<< (owner->getName())<<" " << currentTolls() << " 元";
		Game::showDialog("喔不!", ss.str());
	}
	else
	{
		if (houseLevel<=2)
		{
			if (player->getMoney() >= initialPrice/2)
			{
				stringstream ss;
				ss << "是否要蓋房子(價格:" << initialPrice/2 << ")";
				bool result = Game::showDialog(ss.str(), pair<string, string>("是", "否"), Draw::FIRST);
				if (result)
				{
					//cout << "蓋房成功" << endl;
					player->buyHouse(this);
					this->owner = player;
					drawEstateLevel();
				}
				else
				{
					return;
				}
			}
			else
			{
				stringstream ss;
				ss << "現金不足(價格:" << initialPrice / 2 << ")";
				Game::showDialog("無法蓋房子", ss.str());
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

void EstateBlock::setEstateInfo(Player* player, int level)
{
	houseLevel = level;
	owner = player;
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
		subCursor << Color::B_PLAYER_COLOR[owner->index] << "　　　　";
		subCursor <<pair<string, int>(name.substr(0, 9), 9);
	}
	else
	{
		subCursor <<pair<string, int>(name.substr(0, 8), 8);
	}
}

void EstateBlock::drawBlockInfo()
{
	BaseBlock::drawBlockInfo();
	drawEstateLevel();
}

int EstateBlock::beSelled()
{
	houseLevel = -1;
	owner = NULL;
	drawLocationName();
	drawEstateLevel();
	return initialPrice*0.5;
}

int EstateBlock::currentTolls()
{	
	return tolls[houseLevel];
}

int EstateBlock::getLevelTolls(int level)
{
	return tolls[level];
}

int EstateBlock::getCategory()
{
	return 1;
}

void EstateBlock::drawEstateLevel()
{
	Cursor subCursor = Draw::cursor.getSubCursor(x, y, 2);
	subCursor.add(8, 3);
	if (owner != NULL)
	{
		if(houseLevel > 0)
			subCursor << Color::TAG_CHOOSE_COLOR<<Draw::houseLevelSymbol[houseLevel];
		else
			subCursor << Color::DEF_COLOR << "　";
	}
}

