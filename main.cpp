#include "main.h"
#include "Game.h"

int main()
{
	Game* game = Game::Instance();

	game->Play();

	delete game;
	game = NULL;
	return 0;
}