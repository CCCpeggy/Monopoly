#include "Game.h"

Game::Game()
{

}

//畫出所有畫面
void Game::drawfullgame() {
	drawupstatus();
}

//上方玩家狀態
void Game::drawupstatus()
{
	Grid Gridline;
	cout << Gridline.rowLine[0] << endl;
	Gridline.showplayerlist();
	Gridline.showcurrentplayer();
}
