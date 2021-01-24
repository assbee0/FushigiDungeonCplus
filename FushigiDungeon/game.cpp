#include "game.h"


Game::Game():
	mWindow(nullptr),
	mRenderer(nullptr),
	mTicksCount(0),
	mDeltaTime(0),
	mIsRunning(true),
	mDungeon(nullptr)
{

}
bool Game::Initialize()
{
	mWindow = SDL_CreateWindow(
		"FushigiDungeon", // ¥¿¥¤¥È¥ë
		400,	// Top left x-coordinate of window
		200,	// Top left y-coordinate of window
		640,	// ºá
		480,	// ¿k
		0		
	);
	mRenderer = SDL_CreateRenderer(
		mWindow, // Window to create renderer for
		-1,		 // Usually -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	mDungeon = Dungeon(mRenderer);

	return true;
}

void Game::Loop()
{
	while (mIsRunning)
	{
		Event();
		Update();
		Draw();
	}
}

void Game::Shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::Event()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			mIsRunning = false;
			break;
		}
	}
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
}

void Game::Update()
{
	Tick(60);
}

void Game::Draw()
{
	SDL_SetRenderDrawColor(
		mRenderer,
		0,		// R
		0,		// G 
		255,	// B
		255		// A
	);

	// Clear back buffer
	SDL_RenderClear(mRenderer);

	mDungeon.CreateMap(mRenderer);
	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}

void Game::Tick(int FPS)
{
	int fpsTime = 1000 / FPS;
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + fpsTime))
		;

	mDeltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	mTicksCount = SDL_GetTicks();
}