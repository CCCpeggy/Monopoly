#include "Game.h"

Game::Game() :map("map1")
{
	drawMap();
	StartBlock* start = new StartBlock("起點", 0);
	map.insertBlock(start);
	
	for (size_t i = 1; i < 28; i++)
	{
		if (i == 14)
		{
			FateBlock* fblock = new FateBlock(i, "FateBlock");
			map.insertBlock(fblock);
		}
		else if (i == 27)
		{
			ChanceBlock* cblock = new ChanceBlock(i, "ChanceBlock");
			map.insertBlock(cblock);
		}
		else
		{
			int* toll = new int[4]{ 100,200,300,400 };
			EstateBlock* s = new EstateBlock(i, "EstateBlock", 2000, toll);
			map.insertBlock(s);
		}
	}
	map.calcBlocksLocation();

	player.push_back(Player(0, 50000, 0, 0, map[0]));
	player.push_back(Player(1, 50000, 0, 0, map[0]));
	player.push_back(Player(2, 50000, 0, 0, map[0]));
	player.push_back(Player(3, 50000, 0, 0, map[0]));
	drawupstatus();

	for (int i = 0; i < player.size(); i++) {
		player[i].displayPlayerLocation();
	}

	for (int i = 0; i < map.blockNums; i++) {
		map[i]->drawLocationName();
	}

	int a;
	while (cin >> a)
	{
		player[0].rollDice(map.blockNums);
	}

	
}


//上方玩家狀態
void Game::drawupstatus()
{
	Grid Gridline;
	cout << Gridline.rowLine[0] << endl;
	Gridline.showplayerlist(player[0].getMoney(), player[1].getMoney(), player[2].getMoney(), player[3].getMoney());
	Gridline.showcurrentplayer();
}

void Game::drawMap()
{
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
		cout << boundary[i] << endl;
	}
}


void Game::drawLocationName(vector<string>LocationNameList,vector<EstateBlock*>owner)
{
	HANDLE hOut;
	int c = 0;
	while (c < 28)
	{
		if (c < 8)
		{
			for (int i = 2; i <= 72; i += 10)
			{
				COORD pos{ i + (9 - LocationNameList[c].length()) / 2,1 };
				hOut = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleCursorPosition(hOut, pos);
				cout << LocationNameList[c] << endl;
				c++;
			}
		}
		else if (c >= 8 && c < 15)
		{
			for (int i = 5; i <= 29; i += 4)
			{
				COORD pos{ 72 + (9 - LocationNameList[c].length()) / 2,i };
				hOut = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleCursorPosition(hOut, pos);
				cout << LocationNameList[c] << endl;
				c++;
			}
		}
		else if (c >= 15 && c < 22)
		{
			for (int i = 2; i <= 72; i += 10)
			{
				COORD pos{ i + (9 - LocationNameList[36 - c].length()) / 2,29 };
				hOut = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleCursorPosition(hOut, pos);
				cout << LocationNameList[36 - c] << endl;
				c++;
			}
		}
		else if (c >= 22)
		{
			for (int i = 5; i <= 25; i += 4)
			{
				COORD pos{ 2 + (9 - LocationNameList[50 - c].length()) / 2,i };
				hOut = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleCursorPosition(hOut, pos);
				cout << setw((9 - LocationNameList[50 - c].length()) / 2) << LocationNameList[50 - c] << endl;
				c++;
			}
		}

	}
	COORD endPos{ 0,34 };
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, endPos);
}

void Game::drawDialogue(int mode)
{
	string dialogueBlock[] = { "■———————————————————————■" ,
										   "∥　　　　　　　　　　　　　　　　　　　　　　　∥" ,
										   "∥　　　　　　　　　　　　　　　　　　　　　　　∥" ,
										   "∥　　　　　　　　　　　　　　　　　　　　　　　∥" ,
										   "∥　　　　　　　　　　　　　　　　　　　　　　　∥",
										   "∥　　　　　　　　　　　　　　　　　　　　　　　∥",
										   "∥　　　　　　　　　　　　　　　　　　　　　　　∥",
										   "∥　　　　　　　　　　　　　　　　　　　　　　　∥",
										   "∥　　　　　　　　　　　　　　　　　　　　　　　∥",
											"■———————————————————————■"
	};
	int k = 0;
	HANDLE hOut;
	for (int i = 10; i <= 19; i++)
	{

		COORD pos{ 15,i };
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hOut, pos);
		cout << dialogueBlock[k] << endl;
		k++;
	}
	string title[] = { "確定要購買土地嗎？","機　會","命　運" };
	string choice = "　　　　是　　　　　　　　　　　　　否　　　　";
	COORD posLand{ 17 + (47 - title[0].length()) / 2,12 };
	COORD posCAndF{ 17 + (47 - title[1].length()) / 2,12 };
	COORD posChoice{ 17 , 17 };
	switch (mode)
	{
	case 0:
		SetConsoleCursorPosition(hOut, posLand);
		cout << title[0] << endl;
		SetConsoleCursorPosition(hOut, posChoice);
		cout << choice << endl;
		break;
	case 1:
		SetConsoleCursorPosition(hOut, posCAndF);
		cout << title[1] << endl;
		break;
	case 2:
		SetConsoleCursorPosition(hOut, posCAndF);
		cout << title[2] << endl;
		break;
	}
	COORD endPos{ 0,34 };
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, endPos);

}