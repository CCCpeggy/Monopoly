#include <conio.h>
#include <Windows.h>
class Cursor
{
private:
	int basicX;
	int basicY;
	int rightX;
	int rightY;
	//COORD save;
public:
	Cursor(int = 0, int = 0,int = 1, int = 1);
	void set(int = 0, int = 0, int = 1, int = 1);
	void inputPos(int = 0, int = 0);
	static void inputPos(int drawX, int drawY, int basicX, int basicY, int rightX = 1, int rightY = 1);
};

