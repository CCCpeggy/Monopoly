#include "Cursor.h"

extern HANDLE handleOutput;
const int Cursor::BASIC_NOT_CHANGED = -1;
const int Cursor::RIGHT_NOT_CHANGED = -1;

Cursor::Cursor(int basicX,int basicY, int rightX, int rightY)
	:basicX(basicX),basicY(basicY),rightX(rightX),rightY(rightY),drawX(0),drawY(0)
{
	Color::setTextColor(Color::DEF_COLOR);
	COORD pos;
	pos.X = basicX + drawX * rightX;
	pos.Y = basicY + drawY * rightY;
	SetConsoleCursorPosition(handleOutput, pos);
}

Cursor& Cursor::set(int newBasicX, int newBasicY, int newRightX, int newRightY)
{
	if (newBasicX >= 0) basicX = newBasicX;
	if (newBasicY >= 0) basicY = newBasicY;
	if (newRightX != RIGHT_NOT_CHANGED) rightX = newRightX;
	if (newRightY != RIGHT_NOT_CHANGED) rightY = newRightY;
	drawX = 0;
	drawY = 0;
	COORD pos;
	pos.X = basicX + drawX * rightX;
	pos.Y = basicY + drawY * rightY;
	SetConsoleCursorPosition(handleOutput, pos);
	return *this;
}

Cursor& Cursor::add(int newBasicX, int newBasicY, int newRightX, int newRightY)
{
	return set(newBasicX + basicX, newBasicY + basicY, newRightX, newRightY);
}

Cursor& Cursor::inputPos(int newDrawX, int newDrawY)
{
	drawY = newDrawY;
	drawX = newDrawX;
	COORD pos;
	pos.X = basicX + drawX * rightX;
	pos.Y = basicY + drawY * rightY;
	SetConsoleCursorPosition(handleOutput, pos);
	return *this;
}

Cursor& Cursor::nextLine()
{
	drawX = 0;
	drawY++;
	COORD pos;
	pos.X = basicX + drawX * rightX;
	pos.Y = basicY + drawY * rightY;
	SetConsoleCursorPosition(handleOutput, pos);
	return *this;
}

Cursor& Cursor::nextPos()
{
	drawX++;
	COORD pos;
	pos.X = basicX + drawX * rightX;
	pos.Y = basicY + drawY * rightY;
	SetConsoleCursorPosition(handleOutput, pos);
	return *this;
}

Cursor& Cursor::backPos()
{
	COORD pos;
	pos.X = basicX + drawX * rightX;
	pos.Y = basicY + drawY * rightY;
	SetConsoleCursorPosition(handleOutput, pos);
	return *this;
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

Cursor Cursor::getSubCursor(int newDrawX, int newDrawY, int newRightX, int newRightY) const
{
	return Cursor(basicX + newDrawX * rightX, basicY + newDrawY * rightY, newRightX, newRightY);
}

Cursor& Cursor::operator<<(const unsigned int color) 
{
	Color::setTextColor(color);
	return *this;
}

Cursor& Cursor::operator<<(const pair<string, int> outputString)
{
	int stringLength = outputString.first.length();
	int containerLength = outputString.second;
	int centerX = (containerLength - stringLength) / 2 ;
	if (stringLength < containerLength) {
		COORD pos;
		pos.X = basicX + centerX + drawX * rightX;
		pos.Y = basicY + drawY * rightY;
		SetConsoleCursorPosition(handleOutput, pos);
	}
	cout << outputString.first;
	return *this;
}

Cursor& Cursor::operator<<(const pair<int, int> coordinate) 
{
	inputPos(coordinate.first, coordinate.second);
	return *this;
}

Cursor& Cursor::operator<<(const Cursor&)
{
	return *this;
}

int Cursor::getCursorX() const
{
	return basicX + drawX * rightX;
}

int Cursor::getCursorY() const
{
	return basicY + drawY * rightY;
}

int Cursor::getRightX() const
{
	return rightX;
}

int Cursor::getRightY() const
{
	return rightY;
}

Cursor::~Cursor()
{
	Color::setTextColor(Color::DEF_COLOR);
	Cursor::setCursorHide();
}
