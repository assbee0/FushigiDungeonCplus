#pragma once
#include "SDL.h"
#include "dungeon.h"
class Game 
{
	public:
		Game();
		bool Initialize();
		void Loop();
		void Shutdown();

	private:
		void Event();
		void Update();
		void Draw();
		void Tick(int FPS);

		SDL_Window* mWindow;
		SDL_Renderer* mRenderer;
		Uint32 mTicksCount;
		float mDeltaTime;
		bool mIsRunning;
		Dungeon mDungeon;
};