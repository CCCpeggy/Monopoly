#include "Game.h"
#include <conio.h>
#include <Windows.h>
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
HANDLE handleInput;
HANDLE handleOutput;

//����C��
LPCSTR projectName = "Monopoly";
Game* game = nullptr;
int gameMode;
int dialogIndex = 0; //��ܮؿ������
void(*dialogFunc)() = nullptr; //��ܮةҭn�����ʧ@
string dialogContent = ""; //��ܮ���ܪ���r

//�C����function
void initGame(); //��l�ƹC��
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

	//�������j�p
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	//����Ʀr�����H�վ�����ؤo
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
