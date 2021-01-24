#include "dungeon.h"

Dungeon::Dungeon(SDL_Renderer* render):
	mMap(),
	mWidth(20),
	mHeight(15),
	mTexture(nullptr)
{
	Loading_Surf = IMG_Load("Sprites/ground.png");
	if (!Loading_Surf)
	{
		SDL_Log("Failed to load texture file ");
		return;
	}
	mTexture = SDL_CreateTextureFromSurface(render, Loading_Surf);
}
void Dungeon::CreateMap(SDL_Renderer* render)
{
	mMap[300] = { 0 };
	int i, j = 0;
	
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 20; j++)
		{
			SDL_Rect destR;
			destR.x = j * 32;
			destR.y = i * 32;
			destR.w = 32;
			destR.h = 32;
			SDL_RenderCopy(render, mTexture, NULL, &destR);
		}
}