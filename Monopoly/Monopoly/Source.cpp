#include "Game.h"
#include <vector>
#include <cmath>
#include <string>
using namespace std;

#pragma region  declare

//����e��
HANDLE handleInput = GetStdHandle(STD_INPUT_HANDLE);
HANDLE handleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

//����C��
Game* game = nullptr;
int gameMode;
int dialogIndex = 0; //��ܮؿ������
void(*dialogFunc)() = nullptr; //��ܮةҭn�����ʧ@
string dialogContent = ""; //��ܮ���ܪ���r

//�C����function
void showGame(string);
//�P�_�O�_��txt
bool isTxt(string fileName)
{
	int i = 0;
	for (; i < fileName.length(); i++)
	{
		if (fileName[i] == '.')
		{
			break;
		}
	}
	if (fileName.length() - i >= 3 && fileName[i + 1] == 't'&&fileName[i + 2] == 'x'&&fileName[i + 3] == 't')
	{
		return true;
	}
	else { return false; }
}
//�C�X�ɮײM��
vector<string>listFile()
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

#pragma endregion

int main() {
	//���ù�
	Sleep(1000);
	system("mode con cols=120 lines=50");
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_MENU, 0xb8, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_RETURN, 0x9c, KEYEVENTF_KEYUP, 0);

	SetConsoleTitle("Monopoly");
	Sleep(1000);
	//���ù�
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	//����Ʀr�����H�վ�����ؤo
	vector<string> chooseName = { "�C���}�l", "���Ū��", "�����C��" };
	
	while(true) {
		int fileNameIndex;
		listFile();
		int choose = Game::showMenu("�C�����", chooseName);
		switch (choose) {
		case 0:
			game = new Game;
			delete game;
			system("cls");
			break;
		case 1:
			fileNameIndex = Game::showMenu("����ɦW", listFile(), 0, &showGame);
			if (fileNameIndex >= 0) {
				game = new Game(listFile()[fileNameIndex]);
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

