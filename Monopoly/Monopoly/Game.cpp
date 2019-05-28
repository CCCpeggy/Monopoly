#include "Game.h"

Game::Game(string fileName) :map(),round(0),playerIndex(0),isOver(false)
{
	loadFile(fileName);
	showMap();
	
	while (!isOver) {
		for (; playerIndex < player.size(); playerIndex++) {
			if (isOver = !checkGameStatus() && (!isOver)) break;
			Player* currentPlayer = getPlayer();
			if (currentPlayer->getIsBroken()) continue;
			
			showGameStatus();
			stringstream ss;
			ss << "�� " << round << " �^�X, ���� " << currentPlayer->getName();
			showDialog(ss.str(),"");
			ss.str("");
			ss.clear();

			int choose;
			//���ʧ@�����ܻ��l
			pair<vector<string>, std::map<int, bool(Game::*)(void)> > action;
			bool doNext;
			do {
				action = getAction();
				choose = showMenu("�п�ܰʧ@", action.first);
				doNext = (this->*action.second[choose])();
			} while (!doNext);

			checkMoney();
			
		}
		stockFluctuate();
		playerIndex = 0;
		round++;
	}
	overGame();
}

void Game::loadFile(string fileName)
{
	fstream fin(LOADFILE, ios::in);
	string line, mapName;
	stringstream ss;
	int playerCount;
	//�Ĥ@�� �a�ϦW�� �^�X ���a�ƶq 
	getline(fin, line);
	ss << line;
	ss >> map.mapName >> round >> playerCount;
	ss.str("");
	ss.clear();

	//�a��
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
		else if (blockCategory == -1)
		{
			FateBlock *block = new FateBlock(index, blockName, this);
			map.insertBlock(block);
		}
		else if (blockCategory == -2)
		{
			ChanceBlock *block = new ChanceBlock(index, blockName, this);
			map.insertBlock(block);
		}
		else if (blockCategory == 2)
		{
			BankBlock* block = new BankBlock(blockName, index, this);
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
	//���a
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
	//�Ѳ�
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
	//TODO:
	Player* currentPlayer = getPlayer();
	vector<string> ownItemsNames;
	stringstream ss;
	for (int i = 0; i < currentPlayer->ownedItems.size(); i++) {
		ownItemsNames.push_back(currentPlayer->ownedItems[i]->name);
	}
	int choose = showMenu("�п�ܹD��", ownItemsNames);

	ss << "�T�w�n�ϥ�" << ownItemsNames[choose];
	bool result = Game::showDialog(ss.str(), pair<string, string>("�O", "�_"), Draw::FIRST);
	if (result) {
		//TODOL
		//EstateBlock* block = currentPlayer->ownedEstates[choose];
		//currentPlayer->sellEstate(currentPlayer->ownedEstates[choose]);
		//showAllPlayerStatus();
	}
	return false;
}

bool Game::saveMoney()
{
	//TODO: 
	Player* currentPlayer = getPlayer();
	int money = showNumberDialog("�п�J���B", 0 , currentPlayer->getMoney(), 0, 100, "��");
	currentPlayer->deposit(money);
	return false;
}

bool Game::borrowMoney()
{
	//TODO: 
	Player* currentPlayer = getPlayer();
	int max = currentPlayer->getAsset();
	int money = showNumberDialog("�п�J���B", 0, max, 0, 100, "��");
	currentPlayer->loan(money);
	return false;
}

bool Game::returnMoney()
{
	//TODO: 
	Player* currentPlayer = getPlayer();
	int money = showNumberDialog("�п�J���B", 0, currentPlayer->getDebit(), 0, 100, "��");
	currentPlayer->returnLoan(money);
	return false;
}

bool Game::withdrawMoney()
{
	Player* currentPlayer = getPlayer();
	int money = showNumberDialog("�п�J���B", 0, currentPlayer->getSaving(), 0, 100, "��");
	currentPlayer->withdraw(money);
	return false;
}

bool Game::doStock()
{
	Player* currentPlayer = getPlayer();
	vector<string> ownStockes;
	stringstream ss;
	for (int i = 0; i < stock.size(); i++) {
		ss << stock[i].name << "...X" << stock[i].beOwned[currentPlayer];
		ownStockes.push_back(ss.str());
		ss.str("");
		ss.clear();
	}
	
	int choose = showMenu("�п�ܪѲ�", ownStockes);

	ss << "�аݭn�R�٬O�n��(����:" << stock[choose].prize << ")";
	bool result = Game::showDialog(ss.str(), pair<string, string>("�R", "��"), Draw::FIRST);
	//�R�Ѳ�
	if (result) {
		int max = currentPlayer->getSaving() / stock[choose].prize;
		if (max > 0) {
			int number = showNumberDialog("�аݭn�R�h�ֱi", 1, max, 0, 1, "�i");
			currentPlayer->tradeStock(&stock[choose], true, number);
			showDialog("�������", "");
		}
		else {
			showDialog("�z���s�ڪ��B������");
		}
	}
	//��Ѳ�
	else {
		int max = stock[choose].beOwned[currentPlayer];
		if (max > 0) {
			int number = showNumberDialog("�аݭn��h�ֱi", 1, max, 0, 1, "�i");
			currentPlayer->tradeStock(&stock[choose], false, number);
			showDialog("�������", "");
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
	int total = getPlayerAsset();


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

		action.first.push_back("�Ѳ�");
		action.second[index++] = &Game::doStock;


		if (status == �Ҧ��ʧ@) {
			action.first.push_back("��D��");
			action.second[index++] = &Game::putItem;
		}

		if (status == �Ȧ�) {
			action.first.push_back("����");
			action.second[index++] = &Game::endMenu;
		}

	}

	action.first.push_back("���a��T");
	action.second[index++] = &Game::showPlayStatus;

	return action;
}

double Game::getPlayerAsset()
{
	return getPlayerAsset(getPlayer());
}

double Game::getPlayerAsset(Player* player)
{
	double asset = player->getMoney() + player->getSaving() - player->getDebit();
	vector<EstateBlock*>::iterator iter = player->ownedEstates.begin();
	for (; iter != player->ownedEstates.end(); iter++) {
		asset += (*iter)->initialPrice / 2;
	}
	vector<Stock>::iterator iter2 = stock.begin();
	for (; iter2 != stock.end(); iter2++) {
		asset += iter2->prize * iter2->beOwned[player];
	}
	return asset;
}

void Game::checkMoney()
{
	for (int i = 0; i < player.size(); i++) {
		if (getPlayerAsset(&player[i]) < 0 && !player[i].getIsBroken()) {
			player[i].setBankrupt();
		}
	}
}

bool Game::checkGameStatus()
{
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
		if (!player[i].getIsBroken() && getPlayerAsset(&player[i]) > getPlayerAsset(winner) ) {
			winner = &player[i];
			break;
		}
	}
	stringstream ss;
	ss << winner->getName() << " ���";
	showDialog(ss.str());
}

bool Game::rollDice()
{
	Player* currentPlayer = getPlayer();
	pair<int, int> dice = currentPlayer->rollDice();
	showDice(dice);
	currentPlayer->moveForwardByStep(dice.first + dice.second);
	return true;
}

void Game::overGame()
{
	showWinner();
	int isRestart = showDialog("�O�_���s�}�l",pair<string, string>("�O", "�_"));
	if (!isRestart) {
		Cursor cursor(0, 50);
		ExitProcess(0);
	}
}

bool Game::endMenu()
{
	return true;
}

void Game::showMap()
{
	Draw::drawMap();
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
	Cursor cursor(2, 41, 76);
	cursor << left << setw(2) << playerIndex;
	cursor.nextPos();
	cursor << right << setw(2) << round;
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

bool Game::showPlayStatus()
{
	Draw::drawPlayerInfoFrame();
	player[playerIndex].drawPlayerInfo();
	Draw::drawPlayerInfoTitle(0);
	int number = 0;
	int getKey = keyBoard();
	while (getKey != VK_RETURN) {
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
				//TODO: �����[��
				break;
			case 4:
				//TODO: �����[��
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

int Game::showMenu(string name, vector<string> itemList, int choose)
{
	Draw::drawMenu(itemList, name, choose);
	int getKey = keyBoard();
	while (getKey != VK_RETURN) {
		if (getKey == VK_UP || getKey == VK_DOWN) {
			choose += getKey == VK_DOWN ? 1 : itemList.size()-1;
			choose %= itemList.size();
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

