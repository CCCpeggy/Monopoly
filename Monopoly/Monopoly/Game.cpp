#include "Game.h"

Game::Game() :map("map1")
{
	drawMap();
	drawfullgame();
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

	player.push_back(Player(0, 50000, 0, 0, map[9]));
	player.push_back(Player(1, 50000, 0, 0, map[9]));
	player.push_back(Player(2, 50000, 0, 0, map[9]));
	player.push_back(Player(3, 50000, 0, 0, map[9]));
	for (int i = 0; i < player.size(); i++) {
		player[i].displayPlayerLocation();
	}

	for (int i = 0; i < map.blockNums; i++) {
		map[i]->drawLocationName();
	}

}

//畫出所有畫面
void Game::drawfullgame() {
	drawupstatus();
}

//上方玩家狀態
void Game::drawupstatus()
{
	Grid Gridline;
	cout << Gridline.rowLine[0] << endl;
	Gridline.showplayerlist();
	Gridline.showcurrentplayer();
}

void Game::drawMap()
{
	COORD initPos;
	initPos.X = 0;
	initPos.Y = 0;
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, initPos);
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


void Game::drawLocationName(vector<string>LocationNameList, vector<EstateBlock*>owner)
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

void Game::clearCenter()
{
	string nothing = "　　　　　　　　　　　　　　　　　　　　　　　　　　　　";
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 5; i <= 27; i++)
	{
		COORD pos{ 14,i };
		SetConsoleCursorPosition(hOut, pos);
		cout << nothing;
	}
	COORD endPos{ 0,34 };
	SetConsoleCursorPosition(hOut, endPos);
}