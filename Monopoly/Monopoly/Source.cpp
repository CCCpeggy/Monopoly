#include "Game.h"
#include "Draw.h"
#include <cmath>
using namespace std;

#pragma region define
#define 左 0
#define 上 1
#define 右 2
#define 下 3

#pragma endregion

#pragma region  declare

//關於畫面
HANDLE handleInput = GetStdHandle(STD_INPUT_HANDLE);
HANDLE handleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

//關於遊戲
LPCSTR projectName = "Monopoly";
Game* game = nullptr;
int gameMode;
int dialogIndex = 0; //對話框選取項目
void(*dialogFunc)() = nullptr; //對話框所要做的動作
string dialogContent = ""; //對話框顯示的文字

//遊戲的function
void initGame(); //初始化遊戲
#pragma endregion

int main() {
	//全螢幕
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_MENU, 0xb8, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_RETURN, 0x9c, KEYEVENTF_KEYUP, 0);

	//游標隱藏
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.dwSize = 1;
	lpCursor.bVisible = false;

	SetConsoleTitle(projectName);

	DWORD consoleCnt;
	DWORD consoleMode;
	INPUT_RECORD input;


	//更改視窗大小
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	//控制數字部分以調整視窗尺寸
	game = new Game;
	Draw::drawDialogueBox("測試", "１２３４５６７８1９０１２３４５６７８９０１２３４５６７８９０１２３４５６７８９０１２３４５６７８９");
	
	while (ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &input, 1, &consoleCnt))
	{
		if (input.EventType == KEY_EVENT)
		{
			if (input.Event.KeyEvent.bKeyDown == TRUE)
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
}
