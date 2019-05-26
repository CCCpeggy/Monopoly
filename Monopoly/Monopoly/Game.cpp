#include "Game.h"

Game::Game(string fileName) :map(),round(0),playerIndex(0)
{
	loadFile(fileName);
	showMap();
	
	while (true) {
		for (; playerIndex < player.size(); playerIndex++) {
			showAllPlayerStatus();
			stringstream ss;
			ss << "�� " << round << " �^�X, �� " << playerIndex << " ���a";
			showDialog(ss.str(),"");
			ss.str("");
			ss.clear();

			Player* currentPlayer = getPlayer();

			int choose;
			//���ʧ@�����ܻ��l
			pair<vector<string>, std::map<int, void(Game::*)(void)> > action;
			do {
				action = getAction();
				choose = showMenu("�п�ܰʧ@", action.first);
				(this->*action.second[choose])();
			} while (action.first[choose].compare("�Y��l"));
		}
		stockFluctuate();
		playerIndex = 0;
		round++;
		if (round >= 20) {
			overGame("�F��20�^�X");
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

void Game::sellEstate()
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
	Player* currentPlayer = getPlayer();
	int money = showNumberDialog("�п�J���B", 100 , currentPlayer->getMoney(), 0, 100, "��");
}

void Game::borrowMoney()
{
	//TODO: 
	Player* currentPlayer = getPlayer();
	int max = currentPlayer->getMoney() + currentPlayer->getSaving() - currentPlayer->getDebit();
	int money = showNumberDialog("�п�J���B", 100, max, 0, 100, "��");
}

void Game::returnMoney()
{
	//TODO: 
	Player* currentPlayer = getPlayer();
	int money = showNumberDialog("�п�J���B", 100, currentPlayer->getDebit(), 0, 100, "��");
}

void Game::doStock()
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
	if (result) {
		int number = showNumberDialog("�аݭn�R�h�ֱi", 1, currentPlayer->getSaving() / stock[choose].prize, 0, 1, "�i");
		currentPlayer->tradeStock(&stock[choose], true, number);
	}

	else {
		int number = showNumberDialog("�аݭn��h�ֱi", 1, stock[choose].beOwned[currentPlayer], 0, 1, "�i");
		currentPlayer->tradeStock(&stock[choose], false, number);
	}
	showDialog("�������", "");
	showAllPlayerStatus();
}

pair<vector<string>, map<int, void(Game::*)(void) > > Game::getAction()
{
	Player* currentPlayer = getPlayer();
	pair<vector<string>, std::map<int, void(Game::*)(void)>> action;
	int index = 0;
	int total = currentPlayer->getMoney() + currentPlayer->getSaving() - currentPlayer->getDebit();


	if (total < 0) {
		action.first.push_back("�ŧi�}��");
		action.second[index++] = &Game::playerBroken;
	}

	if (currentPlayer->getMoney() > 0) {
		action.first.push_back("�Y��l");
		action.second[index++] = &Game::rollDice;
	}
	
	action.first.push_back("��D��");
	action.second[index++] = &Game::putTool;

	if (currentPlayer->getMoney() > 0) {
		action.first.push_back("�s��");
		action.second[index++] = &Game::saveMoney;
	}

	if (total > 0) {
		action.first.push_back("�U��");
		action.second[index++] = &Game::borrowMoney;
	}

	if (currentPlayer->getDebit() > 0) {
		action.first.push_back("�ٴ�");
		action.second[index++] = &Game::returnMoney;
	}

	action.first.push_back("�Ѳ�");
	action.second[index++] = &Game::doStock;

	action.first.push_back("���a��T");
	action.second[index++] = &Game::showPlayStatus;

	if (currentPlayer->ownedEstates.size() > 0) {
		action.first.push_back("��a");
		action.second[index++] = &Game::sellEstate;
	}

	return action;
}

void Game::rollDice()
{
	Player* currentPlayer = getPlayer();
	pair<int, int> dice = currentPlayer->rollDice();
	showDice(dice);
	currentPlayer->moveForwardByStep(dice.first + dice.second);
	currentPlayer->location->drawLocationName();
	showAllPlayerStatus();
}

void Game::overGame(string reason)
{
	showDialog("�C������", reason);
	int isRestart = showDialog("�O�_���s�}�l",pair<string, string>("�O", "�_"));
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
				//TODO: �����[��
				break;
			case 2:
				//TODO: �����[��
				break;
			case 3:
				//TODO: �����[��
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

void Game::playerBroken()
{
	stringstream ss;
	ss << "player" << playerIndex + 1 << "�}��";
	showDialog(ss.str(), "");
}

int Game::getDice(int dice)
{
	int change, sum;
	do{
		change = rand() % 5 + 1;
	}while ((dice + change) % 6 + dice == 7);
	return (dice + change) % 6;
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
	for(int i=0;i<10;i++) {
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
		player[i].giveMoney(currentPlayer, money);
	}
}

void Game::giveMoneyFromEveryPlayer(int money)
{
	Player* currentPlayer = getPlayer();
	for (int i = 0; i < player.size(); i++) {
		if (&player[i] == currentPlayer) continue;
		currentPlayer->giveMoney(&player[i], money);
	}
}



