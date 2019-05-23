#include "Game.h"
#include <conio.h>
#include <Windows.h>
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
HANDLE handleInput;
HANDLE handleOutput;

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

	handleInput = GetStdHandle(STD_INPUT_HANDLE);
	handleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTitle(projectName);

	DWORD consoleCnt;
	DWORD consoleMode;
	INPUT_RECORD input;

	GetConsoleMode(handleInput, &consoleMode);
	SetConsoleMode(handleInput, consoleMode & ~ENABLE_LINE_INPUT);

	//更改視窗大小
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	//控制數字部分以調整視窗尺寸
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 800, 420, TRUE);
	game = new Game;
	DialogueBox::drawDialogueBox("Hello world", 1);
	while (ReadConsoleInput(handleInput, &input, 1, &consoleCnt))
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
