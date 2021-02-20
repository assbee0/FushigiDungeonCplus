#include "Game.h"
#include "SDL.h"
#include <Windows.h>

int main(int argc, char* argv[])
{
	Game game;
	// Hide console window
	ShowWindow(GetConsoleWindow(), 0);
	bool success = game.Initialize();
	if (success)
	{
		game.Loop();
	}
	game.Shutdown();
	//system("pause");
	return 0;
}