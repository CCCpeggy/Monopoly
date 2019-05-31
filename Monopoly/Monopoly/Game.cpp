#include "Game.h"

Game::Game(string fileName,bool ableUse) :map(),round(0),playerIndex(0),isOver(false)
{
	loadFile(fileName); 
	if (ableUse) {
		while (!isOver) {
			for (; playerIndex < player.size(); playerIndex++) {
				if ((isOver = !checkGameStatus()) && (isOver)) break;
				Player * currentPlayer = getPlayer();
				if (currentPlayer->getIsBroken()) continue;

				showGameStatus();
				stringstream ss;
				ss << "第 " << round << " 回合, 輪到 " << currentPlayer->getName();
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
			stockFluctuate();
			playerIndex = 0;
			round++;
		}
		showWinner();
	}
}

void Game::loadFile(string fileName)
{
	fstream fin(fileName, ios::in);
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
		BaseBlock* block;
		if (blockCategory == 0){
			block = new StartBlock(blockName, index);
			map.insertBlock(block);
		}
		else if (blockCategory == -1)
		{
			block = new FateBlock(index, blockName, this);
			map.insertBlock(block);
		}
		else if (blockCategory == -2)
		{
			block = new ChanceBlock(index, blockName, this);
			map.insertBlock(block);
		}
		else if (blockCategory == 2)
		{
			block = new BankBlock(blockName, index, this);
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
			block = new EstateBlock(index, blockName, price, toll);
			map.insertBlock(block);
		}
		bool hasRoadBlock;
		if (ss >> hasRoadBlock && hasRoadBlock) {
			block->setRoadBlock(true);
		}
		ss.str("");
		ss.clear();
	}
	map.calcBlocksLocation();
	vector<Player*> playerPtr;
	//玩家
	ss << line;
	ss >> line >> playerIndex;
	ss.str("");
	ss.clear();
	for(int i = 0; i < playerCount; i++) {
		getline(fin, line);
		ss << line;
		int index, position = 0, money = 0, debit = 0, saving = 0;
		if (ss >> index) if (ss >> position) if (ss >> money) if (ss >> debit) if (ss >> saving);
		if(position < 0 || position > map.blockNums)
			player.push_back(Player(index, money, debit, saving, map[0], true, this));
		else
			player.push_back(Player(index, money, debit, saving, map[position], false, this));
		playerPtr.push_back(&player[i]);
		ss.str("");
		ss.clear();
	}
	getline(fin, line);
	//股票
	while (getline(fin, line)) {
		if (line[0] == 'i') break;
		string name;
		double prize = 100;
		
		ss << line;
		if (ss >> prize >> name) {
			if (ss >> prize) {
				stock.push_back(new Stock(name, prize));
				Stock *stockPtr = stock[stock.size() - 1];
				for(int i = 0;i < player.size();i++) player[i].initEachStock(stockPtr, 0);
				int stockPlayerIndex = 0, count = 0;
				while (ss >> stockPlayerIndex >> count) player[stockPlayerIndex].initEachStock(stockPtr, count);
			}
		}
		ss.str("");
		ss.clear();
	}
	//道具
	while (getline(fin, line)) {
		ss << line;
		int inputPlayerIndex;
		ss >> inputPlayerIndex;
		int inputItemIndex, count;
		while (ss >> inputItemIndex >> count)
		{
			if (inputPlayerIndex < player.size() && inputItemIndex < Item::itemList.size()) {
				while(count--)
					player[inputPlayerIndex].addItem(inputItemIndex);
			}
		}

		ss.str("");
		ss.clear();
	}
	fin.close();
	showMap();
}

bool Game::saveFile()
{
	saveFile("saveFile.txt");
	return false;
}

void Game::saveFile(string fileName)
{
	fstream fin(fileName, ios::out);
	//基本資料
	fin << map.mapName << " ";
	fin << round << " ";
	fin << player.size() << endl;
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
			fin << player[i].getDebit() << " ";
			fin << player[i].getSaving();
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

	ss << "確定要使用" << ownItemsNames[choose];
	bool result = Game::showDialog(ss.str(), pair<string, string>("是", "否"), Draw::FIRST);
	if (result) {
		currentPlayer->useItem(choose);
	}
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
	stringstream ss;
	for (int i = 0; i < stock.size(); i++) {
		ss << stock[i]->name << "...X" << currentPlayer->ownedStocks[stock[i]];
		ownStockes.push_back(ss.str());
		ss.str("");
		ss.clear();
	}
	int choose = showMenu("請選擇股票", ownStockes);
	if (choose == 沒有選擇) return false;
	ss << "請問要買還是要賣(價格:" << stock[choose]->prize << ")";
	bool result = Game::showDialog(ss.str(), pair<string, string>("買", "賣"), Draw::FIRST);
	//買股票
	if (result) {
		int max = currentPlayer->getSaving() / stock[choose]->prize;
		if (max > 0) {
			int number = showNumberDialog("請問要買多少張", 1, max, 0, 1, "張");
			if (number != 沒有選擇) {
				currentPlayer->tradeStock(stock[choose], true, number);
				showDialog("交易完成", "");
			}
			
		}
		else {
			showDialog("您的存款金額不足喔");
		}
	}
	//賣股票
	else {
		int max = currentPlayer->ownedStocks[stock[choose]];
		if (max > 0) {
			int number = showNumberDialog("請問要賣多少張", 1, max, 0, 1, "張");
			if (number != 沒有選擇) {
				currentPlayer->tradeStock(stock[choose], false, number);
				showDialog("交易完成", "");
			}
		}
		else {
			showDialog("您沒有此股票喔");
		}
	}
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

		if (status == 所有動作 && stock.size() > 0) {
			action.first.push_back("股票");
			action.second[index++] = &Game::doStock;
		}

		if (status == 所有動作 && currentPlayer->ownedItems.size() > 0) {
			action.first.push_back("放道具");
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
	if (round >= 20) {
		return false;
	}
		
	int livingPlayer = 0;
	for (int i = 0; i < player.size(); i++) {
		if (!player[i].getIsBroken()) livingPlayer++;
	}
	if (livingPlayer <= 1) {
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
	Cursor cursor = Draw::playerStatusCursor.getSubCursor(2, 7, 76);
	cursor << left << setw(2) << playerIndex;
	cursor.nextPos();
	cursor << right << setw(2) << round;
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
	cleanCenter();
	return map[choose];
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
	while (getKey != VK_RETURN) {
		if (getKey == VK_ESCAPE) {
			number = 沒有選擇;
			break;
		}
		Draw::cleanPlayerInfoContent();
		if (getKey == VK_RIGHT || getKey == VK_LEFT) {
			number += getKey == VK_RIGHT ? 1 : 4 ;
			number %= 5;
			switch(number){
			case 0:
				player[playerIndex].drawPlayerInfo();
				break;
			case 1:
				player[playerIndex].drawPlayerAllMoney();
				break;
			case 2:
				player[playerIndex].drawPlayerAllEstate();
				break;
			case 3:
				player[playerIndex].drawPlayerStock();
				break;
			case 4:
				//TODO: 對應涵式
				break;
			}
			Draw::drawPlayerInfoTitle(number);
		}
		getKey = keyBoard();
	}
	cleanCenter();
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

