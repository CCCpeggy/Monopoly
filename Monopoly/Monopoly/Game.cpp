#include "Game.h"

Game::Game()
{

}


void Game::drawupstatus()
{
	Grid Gridline;
	cout << Gridline.rowLine[0] << endl;
	Gridline.showplayerlist();
	Gridline.showcurrentplayer();
}
