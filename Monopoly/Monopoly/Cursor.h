#ifndef _Cursor_
#define _Cursor_
#include <conio.h>
#include <Windows.h>
#include "Color.h"
#include <string>
#include <iostream>
using namespace std;
class Cursor
{
private:
	int basicX;
	int basicY;
	int rightX;
	int rightY;
	int drawX;
	int drawY;
public:
	static const int BASIC_NOT_CHANGED;
	static const int RIGHT_NOT_CHANGED;
	Cursor(int = 0, int = 0,int = 1, int = 1);
	Cursor& set(int = BASIC_NOT_CHANGED, int = BASIC_NOT_CHANGED, int = RIGHT_NOT_CHANGED, int = RIGHT_NOT_CHANGED);
	Cursor& add(int = 0, int = 0, int = RIGHT_NOT_CHANGED, int = RIGHT_NOT_CHANGED);
	Cursor& inputPos(int = 0, int = 0);//改變draw
	Cursor& nextLine();
	Cursor& nextPos();
	static void inputPos(int drawX, int drawY, int basicX, int basicY, int rightX = 1, int rightY = 1);
	static void setCursorHide();
	Cursor getSubCursor(int newDrawX, int newDrawY, int newRightX = 1, int newRightY = 1) const;
	Cursor& operator<< (const unsigned int) ; //設定顏色
	Cursor& operator<< (const pair<string, int>) ; //輸出字串
	Cursor& operator<< (const pair<int, int>) ; //設定座標
	Cursor& operator<< (const Cursor&) ; //不做事
	template <class T>
	Cursor& operator<< (const T outputString) {
		cout << outputString;
		return *this;
	}
		//設定座標
	~Cursor();
};



#endif // !_Cursor_