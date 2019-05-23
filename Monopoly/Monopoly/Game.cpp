#include "Game.h"

Game::Game() :map("map1")
{
	loadFile(LOADFILE);
	drawMap();
	for (int i = 0; i < player.size(); i++) {
		player[i].displayPlayerLocation();
	}


	for (int i = 0; i < map.blockNums; i++) {
		map[i]->drawLocationName();
	}
	drawupstatus();
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



//玩家狀態
void Game::drawupstatus()
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

void Game::drawMap()
{
	Cursor cursor(0, 0);
	string boundary[34] = { "．－－－－．－－－－．－－－－．－－－－．－－－－．－－－－．－－－－．－－－－．",
											 "∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣",
											 "∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣",
											 "∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣",
											 "．－－－－．－－－－．－－－－．－－－－．－－－－．－－－－．－－－－．－－－－．",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "．－－－－．　　　　　　　　　　　　　　　　　　　　　　　　　　　　　．－－－－．",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "．－－－－．　　　　　　　　　　　　　　　　　　　　　　　　　　　　　．－－－－．",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											  "．－－－－．　　　　　　　　　　　　　　　　　　　　　　　　　　　　　．－－－－．",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											  "．－－－－．　　　　　　　　　　　　　　　　　　　　　　　　　　　　　．－－－－．",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											  "．－－－－．　　　　　　　　　　　　　　　　　　　　　　　　　　　　　．－－－－．",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "∣　　　　∣　　　　　　　　　　　　　　　　　　　　　　　　　　　　　∣　　　　∣",
											 "．－－－－．－－－－．－－－－．－－－－．－－－－．－－－－．－－－－．－－－－．",
											 "∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣",
											 "∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣",
											 "∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣　　　　∣",
											 "．－－－－．－－－－．－－－－．－－－－．－－－－．－－－－．－－－－．－－－－．"
	};
	for (int i = 0; i < 34; i++)
	{
		cursor.inputPos(0, i);
		cout << boundary[i];
	}
}