#include "Game.h"
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <map>
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
vector<string> fileNames;

//遊戲的function
void showGame(string);
//判斷是否為txt
bool isTxt(string fileName);
//列出檔案清單
vector<string>listFile();
void newGame();
void loadGame();
void resumeGame();
void finishGame();
bool findFile(string);
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
	vector<string> chooseName;
	map<int, void (*)()> functions;
	srand(time(NULL));
	while(true) {
		chooseName.clear();
		int fileNameIndex;
		fileNames = listFile();
		int index = 0;
		if (findFile("saveFile.txt")) {
			chooseName.push_back("繼續遊戲");
			functions[index++] = &resumeGame;
		}
		chooseName.push_back("遊戲開始");
		functions[index++] = &newGame;

		chooseName.push_back("選擇讀檔");
		functions[index++] = &loadGame;

		chooseName.push_back("結束遊戲");
		functions[index++] = &finishGame;

		int choose = Game::showMenu("遊戲選單", chooseName);
		
		functions[choose]();
	}
	
}

void showGame(string fileName) {
	game = new Game(fileName,false);
}

bool isTxt(string fileName)
{

	{
		int i = 0;
		for (; i < fileName.length(); i++)
		{
			if (fileName[i] == '.')
			{
				break;
			}
		}
		if (fileName.length() - i >= 3 && fileName[i + 1] == 't' && fileName[i + 2] == 'x' && fileName[i + 3] == 't')
		{
			return true;
		}
		else { return false; }
	}
}

vector<string> listFile()
{
	vector<string>fileName;
	string szDir = ".//\*";
	string dir;
	WIN32_FIND_DATA FileData;
	HANDLE hList;
	hList = FindFirstFile(szDir.c_str(), &FileData);
	while (1)
	{
		if (!FindNextFile(hList, &FileData))
		{
			if (GetLastError() == ERROR_NO_MORE_FILES)
				break;
		}
		string a(FileData.cFileName);
		if (isTxt(a))
		{
			fileName.push_back(a);
		}
	}
	FindClose(hList);
	return fileName;
}

void newGame()
{
	game = new Game;
	delete game;
	if (findFile("saveFile2.txt")) {
		rename("saveFile2.txt", "saveFile.txt");
	}
	system("cls");
}

void loadGame()
{
	int fileNameIndex = Game::showMenu("選擇檔名", fileNames, 0, &showGame);
	if (fileNameIndex >= 0) {
		game = new Game(fileNames[fileNameIndex]);
		delete game;
	}
	if (findFile("saveFile2.txt")) {
		rename("saveFile2.txt", "saveFile.txt");
	}
	system("cls");
}

void resumeGame()
{
	game = new Game("saveFile.txt");
	delete game;
	remove("saveFile.txt");
	if (findFile("saveFile2.txt")) {
		rename("saveFile2.txt", "saveFile.txt");
	}
	system("cls");
}

void finishGame()
{
	ExitProcess(0);
}

bool findFile(string findName)
{
	vector<string> fileNames = listFile();
	for (auto name : fileNames) {
		if (name == findName) 
			return true;
	}
	return false;
}

