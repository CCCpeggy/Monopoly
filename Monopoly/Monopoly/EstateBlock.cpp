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
			//�߰ݬO�_�n�R�a return bool
			stringstream ss;
			ss << "�O�_�n�R�a(����:" << initialPrice << ")";
			bool result = Game::showDialog(ss.str(), pair<string, string>("�O", "�_"), Draw::FIRST);
			if (result)
			{
				//cout << "�ʶR���\" << endl;
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
			ss << "�{������(����:" << initialPrice << ")";
			 Game::showDialog("�L�k�R�a", ss.str());
		}
		
	}
	else if(this->owner != player)
	{
		player->giveMoney(owner, currentTolls());
		stringstream ss;
		ss << "��I "<< (owner->getName())<<" " << currentTolls() << " ��";
		Game::showDialog("�ᤣ!", ss.str());
	}
	else
	{
		if (houseLevel<=2)
		{
			if (player->getMoney() >= initialPrice/2)
			{
				stringstream ss;
				ss << "�O�_�n�\�Фl(����:" << initialPrice/2 << ")";
				bool result = Game::showDialog(ss.str(), pair<string, string>("�O", "�_"), Draw::FIRST);
				if (result)
				{
					//cout << "�\�Ц��\" << endl;
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
				ss << "�{������(����:" << initialPrice / 2 << ")";
				Game::showDialog("�L�k�\�Фl", ss.str());
			}
			
		}
	}
}

void EstateBlock::throughEvent(Player* player)
{
	player->outputInformation();
	if (true)//�Y������
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
	// TODO: �󦹳B���J�Ǧ^���z��
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
		subCursor << Color::B_PLAYER_COLOR[owner->index] << "�@�@�@�@";
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
			subCursor << Color::DEF_COLOR << "�@";
	}
}

