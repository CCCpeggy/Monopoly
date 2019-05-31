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
	//��ǭ�
	int basicX;
	int basicY;
	//�[�v��
	int rightX;
	int rightY;
	//���ʭ�
	int drawX;
	int drawY;
public:
	static const int BASIC_NOT_CHANGED;
	static const int RIGHT_NOT_CHANGED;
	//�ظm�G ��ǭ�XY�B�[�v��XY
	Cursor(int = 0, int = 0,int = 1, int = 1);
	//���]�G��ǭȡB�[�v��
	Cursor& set(int = BASIC_NOT_CHANGED, int = BASIC_NOT_CHANGED, int = RIGHT_NOT_CHANGED, int = RIGHT_NOT_CHANGED);
	//���ʡG��ǭȡB�[�v��
	Cursor& add(int = 0, int = 0, int = RIGHT_NOT_CHANGED, int = RIGHT_NOT_CHANGED);
	//���ʿ�J�I
	Cursor& inputPos(int = 0, int = 0);
	//�N��J�I����U�@��@�}�l
	Cursor& nextLine();
	//�N��J�I����P�@�檺�U�@�ӿ�J�I�]���������A�u�O�O�H�[�v�ȧ@�����ʼзǡ^
	Cursor& nextPos();
	static void inputPos(int drawX, int drawY, int basicX, int basicY, int rightX = 1, int rightY = 1);
	static void setCursorHide();
	//���o�lCursor
	Cursor getSubCursor(int newDrawX, int newDrawY, int newRightX = 1, int newRightY = 1) const;
	Cursor& operator<< (const unsigned int) ; //�]�w�C��
	Cursor& operator<< (const pair<string, int>) ; //��X�m���r��]��X�r��B�i��X���ס^
	Cursor& operator<< (const pair<int, int>) ; //�]�w�y��
	Cursor& operator<< (const Cursor&) ; //������
	//��X��r�A���F"unsigned int"�ҥi
	template <class T>
	Cursor& operator<< (const T outputString) {
		cout << outputString;
		return *this;
	}
	int getCursorX() const;
	int getCursorY() const;
	int getRightX() const;
	int getRightY() const;
	~Cursor();
};



#endif // !_Cursor_