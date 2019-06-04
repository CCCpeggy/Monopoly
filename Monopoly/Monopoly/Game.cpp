#include "Game.h"

Game::Game(string fileName,bool ableUse) :map(),round(0),playerIndex(0),isOver(false)
{
	system("cls");
	loadFile(fileName); 
	if (ableUse) {
		while (!isOver) {
			for (; playerIndex < player.size(); playerIndex++) {
				if ((isOver = !checkGameStatus()) && (isOver)) break;
				Player * currentPlayer = getPlayer();
				if (currentPlayer->getIsBroken()) continue;

				showGameStatus();
				stringstream ss;
				ss << "�� " << round + 1 << " �^�X, ���� " << currentPlayer->getName();
				showDialog(ss.str());
				ss.str("");
				ss.clear();

				int choose;
				//���ʧ@�����ܻ��l
				pair<vector<string>, std::map<int, bool(Game::*)(void)> > action;
				bool doNext = false;
				do {
					action = getAction();
					choose = showMenu("�п�ܰʧ@", action.first);
					if (choose != �S�����) doNext = (this->*action.second[choose])();
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

void Game::loadFile(string fileName)
{
	fstream fin(fileName, ios::in);
	string line, mapName;
	stringstream ss;
	int playerCount;
	//�Ĥ@�� �a�ϦW�� �^�X ���a�ƶq 
	getline(fin, line);
	ss << line;
	ss >> map.mapName >> totalRound >> playerCount;
	ss.str("");
	ss.clear();
	std::map<int, BaseBlock*> blockMap;
	//�a��
	while (getline(fin, line)) {
		if (line[0] == 'p')break;
		int index, blockCategory;
		string blockName;
		ss << line;
		ss >> index >> blockName >> blockCategory;
		BaseBlock* block;
		if (blockCategory == 0){
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
	//���a
	ss << line;
	ss >> line >> playerIndex;
	ss.str("");
	ss.clear();
	std::map<int, Player> playerMap;
	std::map<int, vector<pair<int, int> > > ownedEstates;
	for(int i = 0; getline(fin, line) && i < playerCount; i++) {
		if (line[0] > '9') break;
		ss << line;
		int index, position = 0, money = 0, debit = 0, saving = 0, inputNum = 0;;
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
					int blockIndex = (tmp[0] - '0') ;
					if(tmp.size() > 1) blockIndex = (tmp[1] - '0') + blockIndex * 10;
					if (map[blockIndex]->getCategory() == 1) {
						ownedEstates[index].push_back(pair<int, int>(blockIndex, inputNum));
					}
				}
			}
		}
		if(position < 0 || position > map.blockNums)
			playerMap.insert(std::pair<int, Player>(index, Player(index, money, debit, saving, map[0], true, this)));
		else
			playerMap.insert(std::pair<int, Player>(index, Player(index, money, debit, saving, map[position], false, this)));
		ss.str("");
		ss.clear();
	}
	for (auto tmpPlayer : playerMap) {
		player.push_back(tmpPlayer.second);
	}
	playerCount = player.size();

	//�֦��g�a
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
	//�Ѳ�
	if (line[0] == 's') {
		while (getline(fin, line)) {
			if (line[0] > '9') break;
			string name;
			double prize = 100;

			ss << line;
			if (ss >> prize >> name) {
				if (ss >> prize) {
					stock.push_back(new Stock(name, prize));
					Stock* stockPtr = stock[stock.size() - 1];
					for (int i = 0; i < player.size(); i++) player[i].initEachStock(stockPtr, 0);
					int stockPlayerIndex = 0, count = 0;
					while (ss >> stockPlayerIndex >> count) player[stockPlayerIndex].initEachStock(stockPtr, count);
				}
			}
			ss.str("");
			ss.clear();
		}
	}
	//�D��
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
	return false;
}

void Game::saveFile(string fileName)
{
	fstream fin(fileName, ios::out);
	//�򥻸��
	fin << map.mapName << " ";
	fin << totalRound - round << " ";
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
		if (currentPlayer->ownedEstates.size() == 0) return �}��;
		sellEstate();
	}
	return �I��;
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
	int choose = showMenu("�п�ܭn�汼���a", ownEstateNames);
	if (choose == �S�����) return false;
	ss << "�O�_�n��a(����:" << currentPlayer->ownedEstates[choose]->initialPrice / 2 << ")";
	bool result = Game::showDialog(ss.str(), pair<string, string>("�O", "�_"), Draw::FIRST);
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
	int choose = showMenu("�п�ܹD��", ownItemsNames);
	if (choose == �S�����) return false;

	currentPlayer->useItem(choose);
	return false;
}

bool Game::saveMoney()
{
	Player* currentPlayer = getPlayer();
	int money = showNumberDialog("�п�J���B", 0 , currentPlayer->getMoney(), 0, 100, "��");
	if (money != �S�����) 	currentPlayer->deposit(money);
	return false;
}

bool Game::borrowMoney()
{
	Player* currentPlayer = getPlayer();
	int max = currentPlayer->getAsset() - currentPlayer->getMoney();
	int money = showNumberDialog("�п�J���B", 0, max, 0, 100, "��");
	if (money != �S�����) 	currentPlayer->loan(money);
	return false;
}

bool Game::returnMoney()
{
	Player* currentPlayer = getPlayer();
	int money = showNumberDialog("�п�J���B", 0, currentPlayer->getDebit(), 0, 100, "��");
	if (money != �S�����) currentPlayer->returnLoan(money);
	return false;
}

bool Game::withdrawMoney()
{
	Player* currentPlayer = getPlayer();
	int money = showNumberDialog("�п�J���B", 0, currentPlayer->getSaving(), 0, 100, "��");
	if (money != �S�����) currentPlayer->withdraw(money);
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
	int choose = showMenu("�п�ܪѲ�", ownStockes);
	if (choose == �S�����) return false;
	ss << "�аݭn�R�٬O�n��(����:" << stock[choose]->prize << ")";
	bool result = Game::showDialog(ss.str(), pair<string, string>("�R", "��"), Draw::FIRST);
	//�R�Ѳ�
	if (result) {
		int max = currentPlayer->getSaving() / stock[choose]->prize;
		if (max > 0) {
			int number = showNumberDialog("�аݭn�R�h�ֱi", 1, max, 0, 1, "�i");
			if (number != �S�����) {
				currentPlayer->tradeStock(stock[choose], true, number);
				showDialog("�������", "");
			}
			
		}
		else {
			showDialog("�z���s�ڪ��B������");
		}
	}
	//��Ѳ�
	else {
		int max = currentPlayer->ownedStocks[stock[choose]];
		if (max > 0) {
			int number = showNumberDialog("�аݭn��h�ֱi", 1, max, 0, 1, "�i");
			if (number != �S�����) {
				currentPlayer->tradeStock(stock[choose], false, number);
				showDialog("�������", "");
			}
		}
		else {
			showDialog("�z�S�����Ѳ���");
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
		action.first.push_back("�ŧi�}��");
		action.second[index++] = &Game::playerBroken;
	}
	else {
		if (status == �Ҧ��ʧ@) {
			action.first.push_back("�Y��l");
			action.second[index++] = &Game::rollDice;
		}

		if (status == �Ҧ��ʧ@ && currentPlayer->ownedEstates.size() > 0) {
			action.first.push_back("��a");
			action.second[index++] = &Game::sellEstate;
		}


		if (status == �Ȧ� && currentPlayer->getMoney() > 0) {
			action.first.push_back("�s��");
			action.second[index++] = &Game::saveMoney;
		}

		if (status == �Ȧ� && (total - currentPlayer->getMoney()) > 0) {
			action.first.push_back("�U��");
			action.second[index++] = &Game::borrowMoney;
		}

		if (status == �Ȧ� && currentPlayer->getDebit() > 0) {
			action.first.push_back("�ٴ�");
			action.second[index++] = &Game::returnMoney;
		}

		if (status == �Ȧ� && currentPlayer->getSaving() > 0) {
			action.first.push_back("���");
			action.second[index++] = &Game::withdrawMoney;
		}

		if (status == �Ҧ��ʧ@ && stock.size() > 0) {
			action.first.push_back("�Ѳ�");
			action.second[index++] = &Game::doStock;
		}

		if (status == �Ҧ��ʧ@ && currentPlayer->ownedItems.size() > 0) {
			action.first.push_back("��D��");
			action.second[index++] = &Game::putItem;
		}

		if (status == �Ȧ�) {
			action.first.push_back("���}�Ȧ�");
			action.second[index++] = &Game::endMenu;
		}

	}
	action.first.push_back("���a��T");
	action.second[index++] = &Game::showPlayStatus;

	if (status == �Ҧ��ʧ@) {
		action.first.push_back("�Ѳ���T");
		action.second[index++] = &Game::showStock;
	}

	if (status == �Ҧ��ʧ@) {
		action.first.push_back("�g�a��T");
		action.second[index++] = &Game::showBlock;
	}

	if (status == �Ҧ��ʧ@) {
		action.first.push_back("�s��");
		action.second[index++] = &Game::saveFile;
	}
	
	if (status == �Ҧ��ʧ@) {
		action.first.push_back("�^�D�e��");
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
	ss << winner->getName() << " ���";
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
			choose = �S�����;
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

void Game::showChoosingMapMode(void(Game::*function)(void))
{
//	this->function();
	map[0]->drawSelected();
	int choose = 0;
	int getKey = keyBoard();
	while (getKey != VK_RETURN) {
		map[choose]->cleanSelected();
		showBlockContent(choose);
		if (getKey == VK_ESCAPE) {
			choose = �S�����;
			cleanCenter();
			//return nullptr;
		}
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
	int choose = 0;
	drawEstateBlockInfo(choose);
	int getKey = keyBoard();
	while (getKey != VK_RETURN) {
		//����
	}
	return false;
}

void Game::showActionMenu()
{

}

bool Game::playerBroken()
{
	bool result = showDialog("�O�_�T�w�n�ŧi�}��", pair<string, string>("�O", "�_"));
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
			number = �S�����;
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
			chooseIndex = �S�����;
			chooseLine = �S�����;
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
			choose = �S�����;
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
			choose = �S�����;
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
	Cursor cursor = Draw::dialogCursor.getSubCursor(4, 4, 15, 2);
	for (int i = 0; i < 3; i++) {
		cursor << pair<string, int>(Draw::stockInfoTitle[i], 15);
		cursor.nextPos();
	}
	cursor.nextLine();
	int k = 0;
	int page = index / 6;
	if (stock.size() >= page * 6)
	{
		it = stock.begin() + page * 6;
	}
	while (it != stock.end() && k < 6)
	{
		if (index %6 == k)
		{
			cursor << Color::TAG_CHOOSE_COLOR << "�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@";
			cursor << Color::TAG_CHOOSE_COLOR << pair<string, int>((*it)->name, 15);
			cursor.nextPos();
			cursor << Color::TAG_CHOOSE_COLOR << pair<string, int>(to_string((*it)->prize), 15);
			cursor.nextPos();
			stringstream ss;
			string output;
			ss << fixed << setprecision(2) << (*it)->lastChanged;
			ss >> output;
			if ((*it)->lastChanged > 0)
			{
				cursor << Color::B_WHITE_F_RED << pair<string, int>(output, 15);
			}
			else if ((*it)->lastChanged < 0)
			{
				cursor << Color::B_WHITE_F_GREEN << pair<string, int>(output, 15);
			}
			else
			{
				cursor << Color::TAG_CHOOSE_COLOR << pair<string, int>(output, 15);
			}
		}
		else
		{
			cursor << Color::DEF_COLOR << pair<string, int>((*it)->name, 15);
			cursor.nextPos();
			cursor << Color::DEF_COLOR << pair<string, int>(to_string((*it)->prize), 15);
			cursor.nextPos();
			stringstream ss;
			string output;
			ss << fixed << setprecision(2) << (*it)->lastChanged;
			ss >> output;
			if ((*it)->lastChanged > 0)
			{
				cursor << Color::F_RED << pair<string, int>(output, 15);
			}
			else if ((*it)->lastChanged < 0)
			{
				cursor << Color::F_GREEN << pair<string, int>(output, 15);
			}
			else
			{
				cursor << Color::DEF_COLOR << pair<string, int>(output, 15);
			}
		}
		cursor.nextLine();
		k++;
		it++;
	}
}

void Game::drawEstateBlockInfo(int index)
{
	Draw::drawEstateBlockInfoFrame();
	BaseBlock* b = map[2];
	b->OutputBlockInfo();
}
