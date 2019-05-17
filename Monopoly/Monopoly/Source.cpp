#include "Game.h"

Game* game = nullptr;
void showupstatus();

int main() {
	Game game;
	showupstatus();
}

void showupstatus() {
	game->drawupstatus();
}