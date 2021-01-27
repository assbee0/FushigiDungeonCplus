#include "Game.h"
#include "SDL.h"

int main(int argc, char* argv[])
{
	Game game;
	bool success = game.Initialize();
	if (success)
	{
		game.Loop();
	}
	game.Shutdown();
	return 0;
}