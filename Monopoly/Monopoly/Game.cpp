#include "Game.h"

Game::Game(string fileName) :map(),round(0),playerIndex(0)
{
	loadFile(fileName);
	showMap();
	
	while (true) {
		for (; playerIndex < player.size(); playerIndex++) {
			showAllPlayerStatus();
			stringstream ss;
			ss << "第 " << round << " 回合, 第 " << playerIndex << " 玩家";
			showDialog(ss.str(),"");
			ss.str("");
			ss.clear();

			Player* currentPlayer = &player[playerIndex];
			
			int choose;
			//做動作直到選擇骰骰子
			do {
				pair<vector<string>, std::map<int, void(Game::*)(void)> > action = getAction();
				choose = showMenu("請選擇動作", action.first);
				(this->*action.second[choose])();
			} while (choose != 0);
			
			//錢不夠賣房子賣到錢夠，不夠賣就結束遊戲
			if (!noMoney()) {
				ss << "player" << playerIndex + 1 << "破產";
				overGame(ss.str());
				return;
			}
		}
		stockFluctuate();
		playerIndex = 0;
		round++;
		if (round >= 20) {
			overGame("達到20回合");
			return;
		}
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
	stringstream ss;
	for (int i = 0; i < currentPlayer->ownedEstates.size(); i++) {
		ss << currentPlayer->ownedEstates[i]->name << "...$" << currentPlayer->ownedEstates[i]->initialPrice/2;
		ownEstateNames.push_back(ss.str());
		ss.str("");
		ss.clear();
	}
	int choose = showMenu("請選擇要賣掉的地", ownEstateNames);
	
	ss << "是否要賣地(價格:" << currentPlayer->ownedEstates[choose]->initialPrice / 2 << ")";
	bool result = Game::showDialog(ss.str(), pair<string, string>("是", "否"), Draw::FIRST);
	if (result) {
		EstateBlock* block = currentPlayer->ownedEstates[choose];
		currentPlayer->sellEstate(currentPlayer->ownedEstates[choose]);
		block->drawLocationName();
		showAllPlayerStatus();
	}
}

void Game::putTool()
{
	//TODO: 
}

void Game::saveMoney()
{
	//TODO: 
	Player* currentPlayer = &player[playerIndex];
	int money = showNumberDialog("請輸入金額", 0 , currentPlayer->getMoney(), 0, 100, "元");
}

void Game::borrowMoney()
{
	//TODO: 
	Player* currentPlayer = &player[playerIndex];
	int max = currentPlayer->getMoney() + currentPlayer->getSaving() - currentPlayer->getDebit();
	int money = showNumberDialog("請輸入金額", 0, max, 0, 100, "元");
}

void Game::returnMoney()
{
	//TODO: 
	Player* currentPlayer = &player[playerIndex];
	int money = showNumberDialog("請輸入金額", 0, currentPlayer->getDebit(), 0, 100, "元");
}

void Game::doStock()
{
	Player* currentPlayer = &player[playerIndex];
	vector<string> ownStockes;
	stringstream ss;
	for (int i = 0; i < stock.size(); i++) {
		ss << stock[i].name << "...X" << stock[i].beOwned[currentPlayer];
		ownStockes.push_back(ss.str());
		ss.str("");
		ss.clear();
	}
	
	int choose = showMenu("請選擇股票", ownStockes);

	ss << "請問要買還是要賣(價格:" << stock[choose].prize << ")";
	bool result = Game::showDialog(ss.str(), pair<string, string>("買", "賣"), Draw::FIRST);
	if (result) {
		int number = showNumberDialog("請問要買多少張", 0, currentPlayer->getMoney() / stock[choose].prize, 0, 1, "張");
		currentPlayer->tradeStock(&stock[choose], true, number);
	}

	else {
		int number = showNumberDialog("請問要賣多少張", 0, stock[choose].beOwned[currentPlayer], 0, 1, "張");
		currentPlayer->tradeStock(&stock[choose], false, number);
	}
	showDialog("交易完成", "");
	showAllPlayerStatus();
}

pair<vector<string>, map<int, void(Game::*)(void) > > Game::getAction()
{
	Player* currentPlayer = &player[playerIndex];
	pair<vector<string>, std::map<int, void(Game::*)(void)>> action;
	int index = 0;
	action.first.push_back("擲骰子");
	action.second[index++] = &Game::rollDice;

	action.first.push_back("放道具");
	action.second[index++] = &Game::putTool;

	if (currentPlayer->getMoney() > 0) {
		action.first.push_back("存款");
		action.second[index++] = &Game::saveMoney;
	}

	action.first.push_back("貸款");
	action.second[index++] = &Game::borrowMoney;

	if (currentPlayer->getDebit() > 0) {
		action.first.push_back("還款");
		action.second[index++] = &Game::returnMoney;
	}

	action.first.push_back("股票");
	action.second[index++] = &Game::doStock;

	action.first.push_back("玩家資訊");
	action.second[index++] = &Game::showPlayStatus;

	if (currentPlayer->ownedEstates.size() > 0) {
		action.first.push_back("賣地");
		action.second[index++] = &Game::sellEstate;
	}
	

	return action;
}

void Game::rollDice()
{
	Player* currentPlayer = &player[playerIndex];
	pair<int, int> dice = currentPlayer->rollDice();
	showDice(dice);
	//currentPlayer->cleanPlayerLocation();
	int sumDice = dice.first + dice.second;
	currentPlayer->moveForwardByStep(sumDice);
	//currentPlayer->drawPlayerLocation();
	currentPlayer->location->drawLocationName();
	showAllPlayerStatus();
}

void Game::overGame(string reason)
{
	showDialog("遊戲結束", reason);
	int isRestart = showDialog("是否重新開始",pair<string, string>("是", "否"));
	if (!isRestart) {
		Cursor cursor(0, 50);
		ExitProcess(0);
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

void Game::showMapContent()
{
	for (int i = 0; i < player.size(); i++) {
		player[i].drawPlayerLocation();
	}
	for (int i = 0; i < map.blockNums; i++) {
		map[i]->drawLocationName();
	}
}

void Game::showPlayStatus()
{
	player[playerIndex].drawPlayerInfo();
	Draw::drawPlayerInfoTitle(0);
	int number = 0;
	int getKey = keyBoard();
	while (getKey != VK_RETURN) {
		if (getKey == VK_RIGHT || getKey == VK_LEFT) {
			number += getKey == VK_RIGHT ? 1 : 4 ;
			number %= 5;
			switch(number){
			case 0:
				player[playerIndex].drawPlayerInfo();
				break;
			case 1:
				//TODO: 對應涵式
				break;
			case 2:
				//TODO: 對應涵式
				break;
			case 3:
				//TODO: 對應涵式
				break;
			}
			Draw::drawPlayerInfoTitle(number);
		}
		getKey = keyBoard();
	}
	cleanCenter();
}

void Game::showActionMenu()
{

}

int Game::showNumberDialog(string title, int number, int max, int min, int right, string unit)
{
	Draw::drawDialogueBox(title, number, unit);
	int getKey = keyBoard();
	while (getKey != VK_RETURN) {
		if (getKey == VK_RIGHT || getKey == VK_LEFT) {
			number += getKey == VK_RIGHT ? 1 * right : -1 * right;
			number = number > max ? max : number;
			number = number < min ? min : number;
			Draw::drawDialogueBox(title, number, unit);
		}
		getKey = keyBoard();
	}
	cleanCenter();
	return number;
}

void Game::cleanCenter()
{
	Draw::cleanCenter();
}

bool Game::showDialog(string content, pair<string, string> chooseName, bool choose)
{
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

int Game::showMenu(string name, vector<string> items, int choose)
{
	Draw::drawMenu(items, name, choose);
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



