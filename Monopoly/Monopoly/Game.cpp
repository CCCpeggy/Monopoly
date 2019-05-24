#include "Game.h"


const int Game::FRIST = true;
const int Game::SECOND = false;

Game::Game(string fileName) :map()
{
	loadFile(fileName);
	showMap();
	



	//player[0].rollDice(map.blockNums);
}

void Game::loadFile(string fileName)
{
	fstream fin(LOADFILE, ios::in);
	string line, mapName;
	stringstream ss;
	int playerCount;
	//第一行 地圖名稱 回合 玩家數量 
	getline(fin, line);
	ss << line;
	ss >> map.mapName >> round >> playerCount;
	ss.str("");
	ss.clear();

	//地圖
	while (getline(fin, line)) {
		if (line[0] == 'p')break;
		int index, blockCategory;
		string blockName;
		ss << line;
		ss >> index >> blockName >> blockCategory;

		if (blockCategory == 0){
			StartBlock * block = new StartBlock(blockName, index);
			map.insertBlock(block);
		}
		else if (blockCategory == -2)
		{
			FateBlock *block = new FateBlock(index, blockName);
			map.insertBlock(block);
		}
		else if (blockCategory == -1)
		{
			ChanceBlock *block = new ChanceBlock(index, blockName);
			map.insertBlock(block);
		}
		else
		{
			int price;
			int* toll = new int[4];
			ss >> price;
			for (int i = 0; i < 4; i++) {
				int tmp;
				ss >> tmp;
				toll[i] = tmp;
			}
			EstateBlock *block = new EstateBlock(index, blockName, price, toll);
			map.insertBlock(block);
		}
		ss.str("");
		ss.clear();
	}
	map.calcBlocksLocation();
	vector<Player*> playerPtr;
	//玩家
	ss >> line >> playerIndex;
	ss.str("");
	ss.clear();
	for(int i = 0; i < playerCount; i++) {
		getline(fin, line);
		ss << line;
		int index, position, money;
		ss >> index >> position >> money;
		player.push_back(Player(index, money, 0, 0, map[position]));
		playerPtr.push_back(&player[i]);
		ss.str("");
		ss.clear();
	}
	//股票
	while (getline(fin, line)) {
		string name;
		double prize;
		ss << line;
		ss >> prize >> name >> prize;

		stock.push_back(Stock(name, prize, playerPtr));
		ss.str("");
		ss.clear();
	}
	
}

void Game::showMap()
{
	Draw::drawMap();
	showPlayerPosition();
	showBlockContent();
}

void Game::showAllPlayerStatus()
{
	vector<int> dollaerinfo;
	for (int i = 0; i < 4; i++) {
		dollaerinfo.push_back(player[i].getMoney());
		dollaerinfo.push_back(player[i].getDebit());
		dollaerinfo.push_back(player[i].getSaving());
	}
	Draw::showplayerlist(dollaerinfo);
	Draw::showcurrentplayer();
}

void Game::showPlayerInfo()
{
}

void Game::showPlayerPosition(int index)
{
	if (index == ALL) {
		for (int i = 0; i < player.size(); i++) {
			player[i].drawPlayerLocation();
		}
	}
	else {
		player[index].drawPlayerLocation();
	}
}

void Game::showBlockContent()
{
	for (int i = 0; i < map.blockNums; i++) {
		map[i]->drawLocationName();
	}
	showAllPlayerStatus();
}

void Game::showPlayStatus(int index)
{
	player[0].drawPlayerInfo();
}

void Game::showActionMenu()
{

}

void Game::cleanPlayerPosition(int index)
{
	if (index == ALL) {
		for (int i = 0; i < player.size(); i++) {
			player[i].cleanPlayerLocation();
		}
	}
	else {
		player[index].cleanPlayerLocation();
	}
}

void Game::cleanCenter()
{
}

bool Game::showDialog(string content, pair<string, string> chooseName, bool chooseItem)
{
	Draw::drawDialogueBox(content, chooseName, chooseItem);
	return false;
}

