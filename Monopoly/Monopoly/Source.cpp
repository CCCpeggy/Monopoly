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
void initGame(); //��l�ƹC��
#pragma endregion

int main() {
	//���ù�
	system("mode con cols=120 lines=50");
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_MENU, 0xb8, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_RETURN, 0x9c, KEYEVENTF_KEYUP, 0);

	SetConsoleTitle("Monopoly");

	//���ù�
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	//����Ʀr�����H�վ�����ؤo
	vector<string> chooseName = { "�C���}�l", "���Ū��", "�����C��" };
	
	while(true) {
		int fileNameIndex;
		vector<string> fileNames = { "init.txt", "init2.txt", "init3.txt" };
		int choose = Game::showMenu("�C�����", chooseName);
		switch (choose) {
		case 0:
			game = new Game;
			delete game;
			break;
		case 1:
			fileNameIndex = Game::showMenu("����ɦW", fileNames);
			if (fileNameIndex >= 0) {
				game = new Game(fileNames[fileNameIndex]);
				delete game;
			}
			break;
		case 2:
			ExitProcess(0);
			break;
		}
		
	}
	
}
