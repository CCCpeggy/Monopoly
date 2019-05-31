#include "Game.h"
#include <vector>
#include <cmath>
#include <string>
using namespace std;

#pragma region  declare

//關於畫面
HANDLE handleInput = GetStdHandle(STD_INPUT_HANDLE);
HANDLE handleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

//關於遊戲
Game* game = nullptr;
int gameMode;
int dialogIndex = 0; //對話框選取項目
void(*dialogFunc)() = nullptr; //對話框所要做的動作
string dialogContent = ""; //對話框顯示的文字

//遊戲的function
void showGame(string);
#pragma endregion

int main() {
	//全螢幕
	Sleep(1000);
	system("mode con cols=120 lines=50");
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_MENU, 0xb8, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_RETURN, 0x9c, KEYEVENTF_KEYUP, 0);

	SetConsoleTitle("Monopoly");
	Sleep(1000);
	//全螢幕
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	//控制數字部分以調整視窗尺寸
	vector<string> chooseName = { "遊戲開始", "選擇讀檔", "結束遊戲" };
	
	while(true) {
		int fileNameIndex;
		vector<string> fileNames = { "init.txt", "init2.txt", "init3.txt", "saveFile.txt" };
		int choose = Game::showMenu("遊戲選單", chooseName);
		switch (choose) {
		case 0:
			game = new Game;
			delete game;
			system("cls");
			break;
		case 1:
			fileNameIndex = Game::showMenu("選擇檔名", fileNames, 0, &showGame);
			if (fileNameIndex >= 0) {
				game = new Game(fileNames[fileNameIndex]);
				delete game;
			}
			system("cls");
			break;
		case 2:
			ExitProcess(0);
			break;
		}
		
	}
	
}

void showGame(string fileName) {
	game = new Game(fileName,false);
}
