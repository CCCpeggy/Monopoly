#include "Game.h"

Game::Game()
{

}

//�e�X�Ҧ��e��
void Game::drawfullgame() {
	drawupstatus();
}

//�W�誱�a���A
void Game::drawupstatus()
{
	Grid Gridline;
	cout << Gridline.rowLine[0] << endl;
	Gridline.showplayerlist();
	Gridline.showcurrentplayer();
}
