#include "Game.h"

Game::Game(string fileName,bool ableUse, int playerCount) :map(),round(0),playerIndex(0),isOver(false)
{
	system("cls");
	loadFile(fileName, playerCount);
	if (ableUse) {
		while (!isOver) {
			for (; playerIndex < player.size(); playerIndex++) {
				if ((isOver = !checkGameStatus()) && (isOver)) break;
				Player * currentPlayer = getPlayer();
				if (currentPlayer->getIsBroken()) continue;

				showGameStatus();
				stringstream ss;
				ss << "第 " << round + 1 << " 回合, 輪到 " << currentPlayer->getName();
				showDialog(ss.str());
				ss.str("");
				ss.clear();

				int choose;
				//做動作直到選擇骰骰子
				pair<vector<string>, std::map<int, bool(Game::*)(void)> > action;
				bool doNext = false;
				do {
					action = getAction();
					choose = showMenu("請選擇動作", action.first);
					if (choose != 沒有選擇) doNext = (this->*action.second[choose])();
				} while (!doNext);

				checkMoney();

			}
			round++;
			playerIndex = 0;
			if ((isOver = !checkGameStatus()) && (isOver)) break;
			stockFluctuate();
		}
	}
}

void Game::loadFile(string fileName, int inputPlayerCount)
{
	fstream fin(fileName, ios::in);
	string line, mapName;
	stringstream ss;
	int playerCount;

#pragma region FirstLine

	getline(fin, line);
	ss << line;
	ss >> map.mapName >> totalRound >> playerCount >> round;
	if (inputPlayerCount != 沒有選擇) playerCount = inputPlayerCount;
	ss.str("");
	ss.clear();
	std::map<int, BaseBlock*> blockMap;
#pragma endregion

#pragma region Block
	while (getline(fin, line)) {
		if (line[0] == 'p')break;
		int index, blockCategory;
		string blockName;
		ss << line;
		ss >> index >> blockName >> blockCategory;
		BaseBlock * block;
		if (blockCategory == 0) {
			block = new StartBlock(blockName, index);
		}
		else if (blockCategory == -1)
		{
			block = new FateBlock(index, blockName, this);
		}
		else if (blockCategory == -2)
		{
			block = new ChanceBlock(index, blockName, this);
		}
		else if (blockCategory == 2)
		{
			block = new BankBlock(blockName, index, this);
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
			block = new EstateBlock(index, blockName, price, toll);
		}
		bool hasRoadBlock;
		if (ss >> hasRoadBlock && hasRoadBlock) {
			block->setRoadBlock(true);
		}
		blockMap[index] = block;
		ss.str("");
		ss.clear();
	}
	for (auto block : blockMap) {
		map.insertBlock(block.second);
	}

	map.calcBlocksLocation();

#pragma endregion

#pragma region Player

	ss << line;
	ss >> line >> playerIndex;
	ss.str("");
	ss.clear();
	std::map<int, Player> playerMap;
	std::map<int, vector<pair<int, int> > > ownedEstates;
	for (int i = 0; getline(fin, line) && line[0] <= '9'; i++) {
		ss << line;
		int index, position = 0, money = 30000, debit = 0, saving = 0, inputNum = 0;;
		string tmp;
		if (ss >> index >> position >> money) {
			while (ss >> tmp >> inputNum) {
				if (tmp == "d") {
					debit = inputNum;
				}
				else if (tmp == "s") {
					saving = inputNum;
				}
				else {
					int blockIndex = (tmp[0] - '0');
					if (tmp.size() > 1) blockIndex = (tmp[1] - '0') + blockIndex * 10;
					if (map[blockIndex]->getCategory() == 1) {
						ownedEstates[index].push_back(pair<int, int>(blockIndex, inputNum));
					}
				}
			}
		}
		if (position < 0 || position > map.blockNums)
			playerMap.insert(std::pair<int, Player>(index, Player(index, money, debit, saving, map[0], false, this)));
		else
			playerMap.insert(std::pair<int, Player>(index, Player(index, money, debit, saving, map[position], false, this)));
		ss.str("");
		ss.clear();
	}
	int playerTmpIndex;
	std::map<int, Player>::iterator iter;
	for (playerTmpIndex = 0, iter = playerMap.begin(); iter != playerMap.end() && playerTmpIndex < playerCount; playerTmpIndex++, iter++) {
		player.push_back(iter->second);
		player[playerTmpIndex].index = playerTmpIndex;
	}
	for (; playerTmpIndex < playerCount; playerTmpIndex++) {
		player.push_back(Player(playerTmpIndex, 30000, 0, 0, map[0], false, this));
	}

	for (auto node : ownedEstates) {
		int thisPlayerIndex = node.first;
		for (auto subNode : node.second) {
			int estate = subNode.first, houseLevel = subNode.second;
			if (map[estate]->getCategory() == 1) {
				((EstateBlock*)map[estate])->setEstateInfo(&player[thisPlayerIndex], houseLevel);
				player[thisPlayerIndex].ownedEstates.push_back((EstateBlock*)map[estate]);
			}
		}
	}
#pragma endregion
	
#pragma region stock
	if (line[0] == 's') {
		while (getline(fin, line)) {
			if (line[0] > '9') break;
			string name;
			int prize = 100;

			ss << line;
			if (ss >> prize >> name) {
				if (ss >> prize) {
					stock.push_back(new Stock(name, prize));
					Stock* stockPtr = stock[stock.size() - 1];
					for (int i = 0; i < player.size(); i++) player[i].initEachStock(stockPtr, 0);
					char type = 0;
					int value = 0;
					while (ss >> type >> value) {
						if (type > '9') stockPtr->lastChanged = value;
						else player[type - '0'].initEachStock(stockPtr, value);
					}
				}
			}
			ss.str("");
			ss.clear();
		}
	}
#pragma endregion

#pragma region item
	if (line[0] == 'i') {
		while (getline(fin, line)) {
			ss << line;
			int inputPlayerIndex;
			ss >> inputPlayerIndex;
			int inputItemIndex, count;
			while (ss >> inputItemIndex >> count)
			{
				if (inputPlayerIndex < player.size() && inputItemIndex < Item::itemList.size()) {
					while (count--)
						player[inputPlayerIndex].addItem(inputItemIndex);
				}
			}

			ss.str("");
			ss.clear();
		}
	}
	
#pragma endregion

	fin.close();
	showMap();
}

bool Game::saveFile()
{
	stringstream ss;
	ss << "saveFile_";
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	ss << sys.wYear;
	ss << sys.wMonth;
	ss << sys.wDay;
	ss << sys.wHour;
	ss << sys.wMinute;
	ss << sys.wSecond;
	ss << sys.wMilliseconds;
	ss << ".txt";
	saveFile(ss.str());
	showDialog("已存檔" + ss.str());
	return false;
}

void Game::saveFile(string fileName)
{
	fstream fin(fileName, ios::out);
	//基本資料
	fin << map.mapName << " ";
	fin << totalRound - round << " ";
	fin << player.size() << " ";
	fin << round << " ";
	fin << endl;
	for (int i = 0; i < map.blockNums; i++) {
		fin << setfill('0') << setprecision(2) << map[i]->index << " ";
		fin << map[i]->name << " ";
		fin << map[i]->getCategory() << " ";
		if (map[i]->getCategory() == 1) {
			EstateBlock* block = (EstateBlock*)map[i];
			fin << block->initialPrice << " ";
			for (int j = 0; j <= 3; j++) fin << block->getLevelTolls(j) << " ";
		}
		if (map[i]->getHasRoadBlock()) fin << "1 ";
		fin << endl;
	}

	fin << "playerstate " << playerIndex << endl;
	for (int i = 0; i < player.size(); i++) {
		fin << player[i].index << " ";
		if (player[i].getIsBroken()) {
			fin << "-1";
		}
		else{
			fin << player[i].location->index << " ";
			fin << player[i].getMoney() << " ";
			fin << "d " << player[i].getDebit() << " ";
			fin << "s " << player[i].getSaving() << " ";
			for (auto block : player[i].ownedEstates) {
				fin << block->index << " ";
				fin << block->houseLevel << " ";
			}
		}
		fin << endl;
	}

	fin << "stock" << endl;
	for (int i = 0; i < stock.size(); i++) {
		fin << i << " ";
		fin << stock[i]->name << " ";
		fin << stock[i]->prize << " ";
		for (int j = 0; j < player.size(); j++) {
			if (player[j].ownedStocks[stock[i]] > 0) {
				fin << j << " ";
				fin << player[j].ownedStocks[stock[i]] << " ";
			}
		}
		fin << "v ";
		fin << stock[i]->lastChanged << " ";
		fin << endl;
	}
	
	fin << "item" << endl;
	for (int i = 0; i < player.size(); i++) {
		fin << player[i].index << " ";
		for (int j = 0; j < player[i].ownedItems.size(); j++) {
			fin << player[i].ownedItems[j]->index << " ";
			fin << "1 ";
		}
		fin << endl;
	}
	fin.close();
}

void Game::stockFluctuate()
{
	for (int i = 0; i < stock.size(); i++) {
		stock[i]->fluctuate();
	}
	showStock();
}

bool Game::noMoney()
{
	Player* currentPlayer = getPlayer();
	while (currentPlayer->getMoney() < 0){
		if (currentPlayer->ownedEstates.size() == 0) return 破產;
		sellEstate();
	}
	return 富翁;
}

bool Game::sellEstate()
{
	Player* currentPlayer = getPlayer();
	vector<string> ownEstateNames;
	stringstream ss;
	for (int i = 0; i < currentPlayer->ownedEstates.size(); i++) {
		ss << currentPlayer->ownedEstates[i]->name << "...$" << currentPlayer->ownedEstates[i]->initialPrice/2;
		ownEstateNames.push_back(ss.str());
		ss.str("");
		ss.clear();
	}
	int choose = showMenu("請選擇要賣掉的地", ownEstateNames);
	if (choose == 沒有選擇) return false;
	ss << "是否要賣地(價格:" << currentPlayer->ownedEstates[choose]->initialPrice / 2 << ")";
	bool result = Game::showDialog(ss.str(), pair<string, string>("是", "否"), Draw::FIRST);
	if (result) {
		EstateBlock* block = currentPlayer->ownedEstates[choose];
		currentPlayer->sellEstate(currentPlayer->ownedEstates[choose]);
	}
	return false;
}

bool Game::putItem()
{
	Player* currentPlayer = getPlayer();
	vector<string> ownItemsNames;
	stringstream ss;
	for (int i = 0; i < currentPlayer->ownedItems.size(); i++) {
		ownItemsNames.push_back(currentPlayer->ownedItems[i]->name);
	}
	int choose = showMenu("請選擇道具", ownItemsNames);
	if (choose == 沒有選擇) return false;

	currentPlayer->useItem(choose);
	return false;
}

bool Game::saveMoney()
{
	Player* currentPlayer = getPlayer();
	int money = showNumberDialog("請輸入金額", 0 , currentPlayer->getMoney(), 0, 100, "元");
	if (money != 沒有選擇) 	currentPlayer->deposit(money);
	return false;
}

bool Game::borrowMoney()
{
	Player* currentPlayer = getPlayer();
	int max = currentPlayer->getAsset() - currentPlayer->getMoney();
	int money = showNumberDialog("請輸入金額", 0, max, 0, 100, "元");
	if (money != 沒有選擇) 	currentPlayer->loan(money);
	return false;
}

bool Game::returnMoney()
{
	Player* currentPlayer = getPlayer();
	int money = showNumberDialog("請輸入金額", 0, currentPlayer->getDebit(), 0, 100, "元");
	if (money != 沒有選擇) currentPlayer->returnLoan(money);
	return false;
}

bool Game::withdrawMoney()
{
	Player* currentPlayer = getPlayer();
	int money = showNumberDialog("請輸入金額", 0, currentPlayer->getSaving(), 0, 100, "元");
	if (money != 沒有選擇) currentPlayer->withdraw(money);
	return false;
}

bool Game::doStock()
{
	Player* currentPlayer = getPlayer();
	vector<string> ownStockes;
	vector<string>colName;
	vector<vector<string>> word;
	for (int i = 0; i < 6; i++)
	{
		colName.push_back(Draw::stockTradeInfo[i]);
	}

	for (vector<Stock*>::iterator it = stock.begin(); it != stock.end(); it++)
	{
		vector<string>temp(6);
		temp[0] = (*it)->name;
		temp[1] = to_string((*it)->prize);
		if ((*it)->lastChanged >= 0)
		{
			temp[2] = "+";
			temp[2] += to_string((*it)->lastChanged);
		}
		else
		{
			temp[2] = to_string((*it)->lastChanged);
		}
		vector<Stock*>::iterator itt;
		std::map<Stock*, int>::iterator iter;
		for (iter = currentPlayer->ownedStocks.begin(); iter != currentPlayer->ownedStocks.end(); iter++)
		{
			for (itt = stock.begin(); itt != stock.end(); itt++)
			{
				if ((*itt)->name==(*iter).first->name) 
				{
					temp[3] = to_string((*iter).second);
				}
			}
		}
		temp[4] = "買";
		temp[5] = "賣";
		word.push_back(temp);
	}
	do{
		pair<int, int> choose = showInfo("股票交易", colName, word, 6, 4, 5);
		if (choose.first == 沒有選擇 || choose.second == 沒有選擇) break;

		//買股票
		if (choose.second == 4) {
			int max = currentPlayer->getSaving() / stock[choose.first]->prize;
			if (max > 0) {
				int number = showNumberDialog("請問要買多少張", 1, max, 0, 1, "張");
				if (number != 沒有選擇) {
					currentPlayer->tradeStock(stock[choose.first], true, number);
					showDialog("交易完成");
				}
			
			}
			else {
				showDialog("您的存款金額不足喔");
			}
		}
		//賣股票
		else {
			int max = currentPlayer->ownedStocks[stock[choose.first]];
			if (max > 0) {
				int number = showNumberDialog("請問要賣多少張", 1, max, 0, 1, "張");
				if (number != 沒有選擇) {
					currentPlayer->tradeStock(stock[choose.first], false, number);
					showDialog("交易完成", "");
				}
			}
			else {
				showDialog("您沒有此股票喔");
			}
		}
	} while (true);
	return false;
}

pair<vector<string>, map<int, bool(Game::*)(void) > > Game::getAction(int status)
{
	Player* currentPlayer = getPlayer();
	pair<vector<string>, std::map<int, bool(Game::*)(void)>> action;
	int index = 0;
	int total = currentPlayer->getAsset();


	if (total < 0) {
		action.first.push_back("宣告破產");
		action.second[index++] = &Game::playerBroken;
	}
	else {
		if (status == 所有動作) {
			action.first.push_back("擲骰子");
			action.second[index++] = &Game::rollDice;
		}

		if (status == 所有動作 && currentPlayer->ownedEstates.size() > 0) {
			action.first.push_back("賣地");
			action.second[index++] = &Game::sellEstate;
		}


		if (status == 銀行 && currentPlayer->getMoney() > 0) {
			action.first.push_back("存款");
			action.second[index++] = &Game::saveMoney;
		}

		if (status == 銀行 && (total - currentPlayer->getMoney()) > 0) {
			action.first.push_back("貸款");
			action.second[index++] = &Game::borrowMoney;
		}

		if (status == 銀行 && currentPlayer->getDebit() > 0) {
			action.first.push_back("還款");
			action.second[index++] = &Game::returnMoney;
		}

		if (status == 銀行 && currentPlayer->getSaving() > 0) {
			action.first.push_back("領款");
			action.second[index++] = &Game::withdrawMoney;
		}

		if (stock.size() > 0) {
			action.first.push_back("股票市場");
			action.second[index++] = &Game::doStock;
		}

		if (status == 所有動作 && currentPlayer->ownedItems.size() > 0) {
			action.first.push_back("使用道具");
			action.second[index++] = &Game::putItem;
		}

		if (status == 銀行) {
			action.first.push_back("離開銀行");
			action.second[index++] = &Game::endMenu;
		}

	}
	action.first.push_back("玩家資訊");
	action.second[index++] = &Game::showPlayStatus;

	if (status == 所有動作) {
		action.first.push_back("土地資訊");
		action.second[index++] = &Game::showBlock;
	}

	if (status == 所有動作) {
		action.first.push_back("存檔");
		action.second[index++] = &Game::saveFile;
	}
	
	if (status == 所有動作) {
		action.first.push_back("回主畫面");
		action.second[index++] = &Game::backHome;

	}
	return action;
}

Game::~Game()
{
	for (vector<Stock*>::iterator iter = stock.begin(); iter != stock.end(); ) {
		iter = stock.erase(iter);
	}
}

void Game::checkMoney()
{
	for (int i = 0; i < player.size(); i++) {
		if (player[i].getAsset() < 0 && !player[i].getIsBroken()) {
			player[i].setBankrupt();
		}
	}
}

bool Game::checkGameStatus()
{
	if (isOver) return false;
	if (round >= totalRound) {
		showWinner();
		return false;
	}
		
	int livingPlayer = 0;
	for (int i = 0; i < player.size(); i++) {
		if (!player[i].getIsBroken()) livingPlayer++;
	}
	if (livingPlayer <= 1) {
		showWinner();
		return false;
	}
	return true;
	
}

void Game::showWinner()
{
	int i = 0;
	Player* winner = getPlayer();
	for (; i < player.size(); i++) {
		if (!player[i].getIsBroken()) {
			winner = &player[i];
			break;
		}
	}
	for (; i < player.size(); i++) {
		if (!player[i].getIsBroken() && player[i].getAsset() > winner->getAsset() ) {
			winner = &player[i];
			break;
		}
	}
	stringstream ss;
	ss << winner->getName() << " 獲勝";
	showDialog(ss.str());
}

bool Game::backHome()
{
	saveFile("saveFile2.txt");
	isOver = true;
	return true;
}

bool Game::rollDice()
{
	Player* currentPlayer = getPlayer();

	pair<int, int> dice = currentPlayer->rollDice();
	showDice(dice);
	currentPlayer->moveForwardByStep(dice.first + dice.second);
	return true;
}

bool Game::endMenu()
{
	return true;
}

void Game::showMap()
{
	Draw::drawMap((map.blockNums+3) / 4 );
	showMapContent();
	showAllPlayerStatus();
}

void Game::showAllPlayerStatus()
{
	Draw::drawGameStatusFrame();
	for (int i = 0; i < player.size(); i++) {
		player[i].drawStatusPlayerName();
		player[i].drawPlayerMoneyStatus();
	}
	showGameStatus();
}

void Game::showGameStatus() {
	Cursor cursor = Draw::playerStatusCursor.getSubCursor(2, 8, 76);
	cursor << left << setw(6) << player[playerIndex].getName();
	cursor.nextPos();
	cursor << right << setw(2) << round + 1;
}

BaseBlock* Game::showChoosingMapMode(string content)
{
	Draw::drawDialogueBox(content);
	map[0]->drawSelected();
	int choose = 0;
	int getKey = keyBoard();
	while (getKey != VK_RETURN) {
		map[choose]->cleanSelected();
		showBlockContent(choose);
		if (getKey == VK_ESCAPE) {
			choose = 沒有選擇;
			cleanCenter();
			return nullptr;
		}
		int tmpX = map[choose]->x, tmpY = map[choose] -> y;
		if (getKey == VK_RIGHT) {
			tmpX++;
		}
		else if (getKey == VK_LEFT) {
			tmpX--;
		}
		else if (getKey == VK_DOWN) {
			tmpY++;
		}
		else if (getKey == VK_UP) {
			tmpY--;
		}
		int nextChoose = (choose + 1) % map.blockNums;
		int lastChoose = (choose - 1 + map.blockNums) % map.blockNums;
		if (map[nextChoose]->x == tmpX && map[nextChoose]->y == tmpY) choose = nextChoose;
		else if (map[lastChoose]->x == tmpX && map[lastChoose]->y == tmpY) choose = lastChoose;
		map[choose]->drawSelected();
		getKey = keyBoard();
	}
	map[choose]->cleanSelected();
	showBlockContent(choose);
	cleanCenter();
	return map[choose];
}

void Game::showChoosingMapMode(void(Game::*function)(int))
{
	int choose = 0;
	(this->*function)(choose);
	map[0]->drawSelected();
	int getKey = keyBoard();
	while (getKey != VK_ESCAPE) {
		map[choose]->cleanSelected();
		showBlockContent(choose);
		int tmpX = map[choose]->x, tmpY = map[choose]->y;
		if (getKey == VK_RIGHT) {
			tmpX++;
		}
		else if (getKey == VK_LEFT) {
			tmpX--;
		}
		else if (getKey == VK_DOWN) {
			tmpY++;
		}
		else if (getKey == VK_UP) {
			tmpY--;
		}
		int nextChoose = (choose + 1) % map.blockNums;
		int lastChoose = (choose - 1 + map.blockNums) % map.blockNums;
		if (map[nextChoose]->x == tmpX && map[nextChoose]->y == tmpY) choose = nextChoose;
		else if (map[lastChoose]->x == tmpX && map[lastChoose]->y == tmpY) choose = lastChoose;
		map[choose]->drawSelected();
		(this->*function)(choose);
		getKey = keyBoard();
	}
	map[choose]->cleanSelected();
	showBlockContent(choose);
	cleanCenter();
}

void Game::showMapContent()
{
	for (int i = 0; i < player.size(); i++) {
		if (!player[i].getIsBroken())
			player[i].drawPlayerLocation();
	}
	for (int i = 0; i < map.blockNums; i++) {
		map[i]->drawLocationName();
		map[i]->drawBlockInfo();
	}
}

void Game::showBlockContent(int index)
{
	map[index]->drawLocationName();
	map[index]->drawBlockInfo();
	for (int i = 0; i < player.size(); i++) {
		if(!player[i].getIsBroken()&& player[i].location->index==index)
			player[i].drawPlayerLocation();
	}
}

bool Game::showPlayStatus()
{
	Draw::drawPlayerInfoFrame();
	player[playerIndex].drawPlayerInfo();
	Draw::drawPlayerInfoTitle(0);
	int number = 0;
	int getKey = keyBoard();
	while (getKey != VK_ESCAPE) {
		bool choosed = false;
		if (getKey == VK_RIGHT || getKey == VK_LEFT) {
			Draw::cleanPlayerInfoContent();
			number += getKey == VK_RIGHT ? 1 : 4 ;
			number %= 5;
			Draw::drawPlayerInfoTitle(number);
		}
		else if (getKey == VK_RETURN || getKey == VK_DOWN) {
			Draw::cleanPlayerInfoContent();
			choosed = true;
		}
		if (getKey == VK_RIGHT || getKey == VK_LEFT ||getKey == VK_RETURN || getKey == VK_DOWN) {
			switch (number) {
			case 0:
				player[playerIndex].drawPlayerInfo(choosed);
				break;
			case 1:
				player[playerIndex].drawPlayerAllMoney(choosed);
				break;
			case 2:
				player[playerIndex].drawPlayerAllEstate(choosed);
				break;
			case 3:
				player[playerIndex].drawPlayerStock(choosed);
				break;
			case 4:
				player[playerIndex].drawPlayerItem(choosed);
				break;
			}
		}
		getKey = keyBoard();
	}
	cleanCenter();
	return false;
}

bool Game::showStock()
{
	int choose = 0;
	drawStockInfo(choose);
	int getKey = keyBoard();
	while (getKey != VK_RETURN && getKey != VK_ESCAPE) {
		if (getKey == VK_UP || getKey == VK_DOWN) {
			choose += getKey == VK_DOWN ? 1 : stock.size() - 1;
			choose %= stock.size();
			drawStockInfo(choose);
		}
		getKey = keyBoard();
	}
	cleanCenter();
	return false;
}

bool Game::showBlock()
{
	Draw::drawEstateBlockInfoFrame();
	showChoosingMapMode(&Game::drawEstateBlockInfo);
	/*
	int choose = 0;
	(choose);
	int getKey = keyBoard();
	while (getKey != VK_RETURN) {
		//移動
	}*/
	return false;
}

void Game::showActionMenu()
{

}

bool Game::playerBroken()
{
	bool result = showDialog("是否確定要宣告破產", pair<string, string>("是", "否"));
	if (result) {
		getPlayer()->setBankrupt();
	}
	return result;
}

int Game::getDice(int dice)
{
	int change, sum;
	do{
		change = rand() % 5;
	}while ((dice + change) % 6 + dice == 6);
	return (dice + change) % 6 + 1;
}

int Game::showNumberDialog(string title, int number, int max, int min, int right, string unit)
{
	Draw::drawDialogueBox(title, number, unit);
	int getKey = keyBoard();
	while (getKey != VK_RETURN) {
		if (getKey == VK_ESCAPE) {
			number = 沒有選擇;
			break;
		}
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
		if (getKey == VK_ESCAPE) {
			choose = Draw::SECOND;
			break;
		}
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
	while (keyBoard() != VK_RETURN) {	}
	cleanCenter();
}

void Game::showDice(pair<int, int> dice)
{
	pair<int, int> tmpDice = dice;
	for(int i=0;i<5;i++) {
		tmpDice.first = getDice(tmpDice.first);
		tmpDice.second = getDice(tmpDice.second);
		Draw::drawDice(tmpDice.first, tmpDice.second);
		Sleep(100);
	}

	Draw::drawDice(dice.first, dice.second);
	while (keyBoard() != VK_RETURN) {}
	cleanCenter();
}

void Game::showPlayerInfo(vector<string> word, bool choosed)
{
	if (choosed) {
		int chooseLine = 0;
		Draw::drawInfo("", word, chooseLine, false);
		int getKey = keyBoard();
		if (word.size() <= 0) return;
		while (getKey != VK_ESCAPE && !(chooseLine == 0 && getKey == VK_UP)) {
			if (getKey == VK_UP || getKey == VK_DOWN) {
				chooseLine += getKey == VK_DOWN ? 1 : word.size() - 1;
				chooseLine %= word.size();
			}
			Draw::cleanPlayerInfoContent();
			Draw::drawInfo("", word, chooseLine, false);
			getKey = keyBoard();
		}
	}
	Draw::cleanPlayerInfoContent();
	Draw::drawInfo("", word, -1, false);
	return;
}

void Game::showPlayerInfo(string title, vector<string> colName, vector<vector<string> > word, int n, bool choosed)
{
	if (choosed) {
		int chooseIndex = -1;
		int chooseLine = 0;
		Draw::drawInfo(title, colName, word, chooseIndex, n, chooseLine, false);
		int getKey = keyBoard();
		if (word.size() <= 0) return;
		while (getKey != VK_ESCAPE && !(chooseLine == 0 && getKey == VK_UP)) {
			if (getKey == VK_UP || getKey == VK_DOWN) {
				chooseLine += getKey == VK_DOWN ? 1 : word.size() - 1;
				chooseLine %= word.size();
			}
			Draw::cleanPlayerInfoContent();
			Draw::drawInfo(title, colName, word, chooseIndex, n, chooseLine, false);
			getKey = keyBoard();
		}
	}
	Draw::cleanPlayerInfoContent();
	Draw::drawInfo(title, colName, word, -1, n, -1, false);
	return;
}

pair<int, int> Game::showInfo(string title, vector<string> colName, vector<vector<string> > word, int n, int minIndex, int maxIndex)
{
	int chooseIndex = minIndex;;
	int chooseLine = 0;
	Draw::drawInfo(title, colName, word, chooseIndex, n, chooseLine);
	int getKey = keyBoard();
	while (getKey != VK_RETURN) {
		if (getKey == VK_ESCAPE) {
			chooseIndex = 沒有選擇;
			chooseLine = 沒有選擇;
			break;
		}
		if (getKey == VK_UP || getKey == VK_DOWN) {
			chooseLine += getKey == VK_DOWN ? 1 : word.size() - 1;
			chooseLine %= word.size();
			Draw::drawInfo(title, colName, word, chooseIndex, n, chooseLine);
		}
		else if (getKey == VK_LEFT || getKey == VK_RIGHT) {
			chooseIndex -= minIndex;
			chooseIndex += getKey == VK_RIGHT ? 1 : (maxIndex - minIndex);
			chooseIndex %= (maxIndex - minIndex + 1);
			chooseIndex += minIndex;
			Draw::drawInfo(title, colName, word, chooseIndex, n, chooseLine);
		}
		getKey = keyBoard();
	}
	cleanCenter();
	return pair<int, int>(chooseLine, chooseIndex);
}

int Game::showInfo(string title, vector<string> word)
{
	int choose = 0;
	Draw::drawInfo(title, word, choose);
	int getKey = keyBoard();
	while (getKey != VK_RETURN) {
		if (getKey == VK_ESCAPE) {
			choose = 沒有選擇;
			break;
		}
		if (getKey == VK_UP || getKey == VK_DOWN) {
			choose += getKey == VK_DOWN ? 1 : word.size() - 1;
			choose %= word.size();
			Draw::drawInfo(title, word, choose);
		}
		getKey = keyBoard();
	}
	cleanCenter();
	return choose;
}

int Game::showMenu(string name, vector<string> itemList, int choose, void(*function)(string))
{
	if (function != nullptr) function(itemList[choose]);
	Draw::drawMenu(itemList, name, choose);
	int getKey = keyBoard();
	while (getKey != VK_RETURN) {
		if (getKey == VK_ESCAPE) {
			choose = 沒有選擇;
			break;
		}
		if (getKey == VK_UP || getKey == VK_DOWN) {
			choose += getKey == VK_DOWN ? 1 : itemList.size()-1;
			choose %= itemList.size();
			if (function != nullptr) function(itemList[choose]);
			Draw::drawMenu(itemList, name, choose);
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

Player* Game::getPlayer()
{
	return &player[playerIndex];
}

void Game::getMoneyFromEveryPlayer(int money)
{
	Player* currentPlayer = getPlayer();
	for (int i = 0; i < player.size(); i++) {
		if (&player[i] == currentPlayer) continue;
		if (player[i].getIsBroken()) continue;
		player[i].giveMoney(currentPlayer, money);
	}
	showAllPlayerStatus();
}

void Game::giveMoneyToEveryPlayer(int money)
{
	Player* currentPlayer = getPlayer();
	for (int i = 0; i < player.size(); i++) {
		if (&player[i] == currentPlayer) continue;
		if (player[i].getIsBroken()) continue;
		currentPlayer->giveMoney(&player[i], money);
	}
	showAllPlayerStatus();
}

void Game::drawStockInfo(int index)
{
	Draw::drawStockInfoFrame();
	vector<Stock*>::iterator it;
	stringstream ss;
	Cursor cursor = Draw::dialogCursor.getSubCursor(4, 4, 15, 1);
	for (int i = 0; i < 3; i++) {
		cursor << pair<string, int>(Draw::stockInfoTitle[i], 15);
		cursor.nextPos();
	}
	cursor.add(0, 3, 15, 2);
	int k = 0;
	int page = index / 6;
	if (stock.size() >= page * 6)
	{
		it = stock.begin() + page * 6;
	}
	while (it != stock.end() && k < 6)
	{
		double rate = (double)(*it)->lastChanged / ((*it)->prize - (*it)->lastChanged);
		ss << fixed << setprecision(2) << (*it)->lastChanged;
		unsigned int color = Color::DEF_COLOR, numberColor = Color::DEF_COLOR;
		if (index %6 == k)
		{
			color = numberColor = Color::TAG_CHOOSE_COLOR;
			if (rate > 0) numberColor = Color::B_WHITE_F_RED;
			else if (rate < 0) numberColor = Color::B_WHITE_F_GREEN;
		}
		else if(rate >= 0.095)
		{
			color = numberColor = Color::B_RED;
		}
		else if (rate < -0.095)
		{
			color = numberColor = Color::B_GREEN;
		}
		else
		{
			color = numberColor = Color::DEF_COLOR;
			if (rate > 0) numberColor = Color::F_RED;
			else if (rate < 0) numberColor = Color::F_GREEN;
		}
		cursor << color << "　　　　　　　　　　　　　　　　　　　　　　";
		cursor.backPos();
		cursor << pair<string, int>((*it)->name, 15);
		cursor.nextPos();
		cursor << pair<string, int>(to_string((*it)->prize), 15);
		cursor.nextPos();
		cursor << numberColor << pair<string, int>(ss.str(), 15);
		cursor.nextLine();

		ss.str("");
		ss.clear();
		k++;
		it++;
	}
}

void Game::drawEstateBlockInfo(int index)
{
	Draw::cleanPlayerInfoContent();
	map[index]->drawBlockInfoCenter();
}
