#include "Game.h"

Game::Game(string fileName) :map(),round(0),playerIndex(0)
{
	loadFile(fileName);
	showMap();
	while (true) {
		for (; playerIndex < player.size(); playerIndex++) {
			showAllPlayerStatus();
			Player* currentPlayer = &player[playerIndex];
			pair<int, int> dice = currentPlayer->rollDice();
			showDice(dice);
			currentPlayer->cleanPlayerLocation();
			int sumDice = dice.first + dice.second;
			currentPlayer->moveForwardByStep(sumDice);
			currentPlayer->drawPlayerLocation();
			currentPlayer->location->drawLocationName();
			showAllPlayerStatus();
			if (!noMoney()) {
				stringstream ss;
				ss << "player" << playerIndex + 1 << "破產";
				showDialog("遊戲結束", ss.str());
				return;
			}
		}
		stockFluctuate();
		playerIndex = 0;
		round++;
	}
	
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

void Game::stockFluctuate()
{
	for (int i = 0; i < stock.size(); i++) {
		stock[i].fluctuate();
	}
}

bool Game::noMoney()
{
	Player* currentPlayer = &player[playerIndex];
	while (currentPlayer->getMoney() < 0){
		if (currentPlayer->ownedEstates.size() == 0) return 破產;
		sellEstate();
	}
	return 富翁;
}

void Game::sellEstate()
{
	Player* currentPlayer = &player[playerIndex];
	vector<string> ownEstateNames;
	for (int i = 0; i < currentPlayer->ownedEstates.size(); i++)
		ownEstateNames.push_back(currentPlayer->ownedEstates[i]->name);
	int choose = showMenu("請選擇要賣掉的地", ownEstateNames);
	stringstream ss;
	ss << "是否要賣地(價格:" << currentPlayer->ownedEstates[choose]->initialPrice << ")";
	bool result = Game::showDialog(ss.str(), pair<string, string>("是", "否"), Draw::FIRST);
	if (result) {
		currentPlayer->buyHouse(currentPlayer->ownedEstates[choose]);
		showAllPlayerStatus();
	}
}

void Game::showMap()
{
	Draw::drawMap();
	showMapContent();
	showAllPlayerStatus();
}

void Game::showAllPlayerStatus()
{
	vector<int> dollaerinfo;
	for (int i = 0; i < 4; i++) {
		dollaerinfo.push_back(player[i].getMoney());
		dollaerinfo.push_back(player[i].getDebit());
		dollaerinfo.push_back(player[i].getSaving());
	}
	Draw::drawPlayerList(dollaerinfo);
	Draw::drawCurrentPlayer(playerIndex, round);
}

void Game::showPlayerInfo()
{
}

void Game::showMapContent()
{
	for (int i = 0; i < player.size(); i++) {
		player[i].drawPlayerLocation();
	}
	for (int i = 0; i < map.blockNums; i++) {
		map[i]->drawLocationName();
	}
}

void Game::showPlayStatus(int index)
{
	player[0].drawPlayerInfo();
}

void Game::showActionMenu()
{

}

void Game::cleanCenter()
{
	Draw::cleanCenter();
}

bool Game::showDialog(string content, pair<string, string> chooseName, bool chooseItem)
{
	bool choose = chooseItem;
	Draw::drawDialogueBox(content, chooseName, choose);
	int getKey = keyBoard();
	while(getKey != VK_RETURN) {
		if (getKey == VK_RIGHT || getKey == VK_LEFT) {
			choose = !choose;
			Draw::drawDialogueBox(content, chooseName, choose);
		}
		getKey = keyBoard();
	}
	cleanCenter();
	return choose;
}

void Game::showDialog(string title, string content)
{
	Draw::drawDialogueBox(title, content);
	int getKey = keyBoard();
	while (getKey != VK_RETURN) {	}
	cleanCenter();
}

void Game::showDice(pair<int, int> dice)
{
	Draw::drawDice(dice.first, dice.second);
	int getKey = keyBoard();
	while (getKey != VK_RETURN) {}
	cleanCenter();
}

int Game::showMenu(string name, vector<string> items, int index)
{
	int choose = index;
	Draw::drawMenu(items, name, index);
	int getKey = keyBoard();
	while (getKey != VK_RETURN) {
		if (getKey == VK_UP || getKey == VK_DOWN) {
			choose += getKey == VK_DOWN ? 1 : items.size()-1;
			choose %= items.size();
			Draw::drawMenu(items, name, choose);
		}
		getKey = keyBoard();
	}
	cleanCenter();
	return choose;
}

int Game::keyBoard()
{
	DWORD consoleCnt;
	INPUT_RECORD input;
	while (ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &input, 1, &consoleCnt))
	{
		if (input.EventType == KEY_EVENT && input.Event.KeyEvent.bKeyDown == TRUE)
		{
			switch (input.Event.KeyEvent.wVirtualKeyCode) {
			case VK_UP: //26
			case VK_DOWN: //28
			case VK_LEFT: //25
			case VK_RIGHT: //27
			case VK_RETURN:
			case VK_ESCAPE:
				return input.Event.KeyEvent.wVirtualKeyCode;
			}

		}
	}
	
}



