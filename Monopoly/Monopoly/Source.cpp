#include "Game.h"
#include <cmath>
using namespace std;

#pragma region define
#define �� 0
#define �W 1
#define �k 2
#define �U 3

#pragma endregion

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
	game = new Game;
	Cursor::setCursorHide();
	DWORD consoleCnt;
	DWORD consoleMode;
	INPUT_RECORD input;
	while (ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &input, 1, &consoleCnt))
	{
		if (input.EventType == KEY_EVENT && input.Event.KeyEvent.bKeyDown == TRUE)
		{
			switch (input.Event.KeyEvent.wVirtualKeyCode) {
				//input.Event.KeyEvent.wVirtualKeyCode - VK_LEFT
			case VK_UP: //26
			case VK_DOWN: //28
				break;
			case VK_LEFT: //25
			case VK_RIGHT: //27
				break;
			case VK_RETURN:
				break;
			case VK_ESCAPE:
				break;
			default:
				break;
			}
			
		}
	}
}
