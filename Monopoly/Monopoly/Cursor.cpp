#include "Cursor.h"

extern HANDLE handleOutput;

Cursor::Cursor(int basicX,int basicY, int rightX, int rightY)
	:basicX(basicX),basicY(basicY),rightX(rightX),rightY(rightY)
{

}

void Cursor::set(int newBasicX, int newBasicY, int newRightX, int newRightY)
{
	basicX = newBasicX;
	basicY = newBasicY;
	rightX = newRightX; 
	rightY = newRightY;
}

void Cursor::inputPos(int drawX, int drawY)
{
	COORD pos;
	pos.X = basicX + drawX * rightX;
	pos.Y = basicY + drawY * rightY;
	SetConsoleCursorPosition(handleOutput, pos);
}

void Cursor::inputPos(int drawX, int drawY, int basicX, int basicY, int rightX, int rightY)
{
	COORD pos;
	pos.X = basicX + drawX * rightX;
	pos.Y = basicY + drawY * rightY;
	SetConsoleCursorPosition(handleOutput, pos);
}

void Cursor::setCursorHide()
{
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.dwSize = 1;
	lpCursor.bVisible = false;
	SetConsoleCursorInfo(handleOutput, &lpCursor);
}
