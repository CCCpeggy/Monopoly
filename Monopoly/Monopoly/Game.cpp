#include "Game.h"

Game::Game()
{
	Grid Gridline;
	cout << Gridline.rowLine[0] << endl;
	Gridline.showplayerlist();
	Gridline.showcurrentplayer();
}


Game::~Game()
{
}
