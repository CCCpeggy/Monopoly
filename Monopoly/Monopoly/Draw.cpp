#include "Draw.h"



Grid::Grid()
{
	rowLine[0] = "�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X";
	rowLine[1] = "�U�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�U";
}


void Grid::showplayerlist()
{
	cout << verticalBar;
	whiteonBlue();
	cout << left << setw(14) << "1";
	defaultcolor();
	cout << verticalBar;
	whiteonGreen();
	cout << left << setw(14) << "2";
	defaultcolor();
	cout << verticalBar;
	whiteonCyan();
	cout << left << setw(14) << "3";
	defaultcolor();
	cout << verticalBar;
	whiteonRed();
	cout << left << setw(14) << "4";
	defaultcolor();
	cout << verticalBar << endl << verticalBar;
	//tmpdollar����|�������a����
	cout << " " << left << setw(13) << tmpdollar << verticalBar;
	cout << " " << left << setw(13) << tmpdollar << verticalBar;
	cout << " " << left << setw(13) << tmpdollar << verticalBar;
	cout << " " << left << setw(13) << tmpdollar << verticalBar;
	cout << endl << rowLine[1] << endl;
}

void Grid::showcurrentplayer() {
	cout << verticalBar << "�ثe�C����" << setw(42) << " " << "��e�^�X��" << verticalBar << endl;
	cout << verticalBar << " " << "1" << setw(59) << " " << "1" << verticalBar << endl;

	cout << rowLine[1];
}