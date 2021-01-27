#include "Dungeon.h"

Dungeon::Dungeon(SDL_Renderer* render):
	mMap(),
	mWidth(20),
	mHeight(15),
	mTexture(nullptr)
{
	mMap[300] = { 0 };
}
void Dungeon::CreateMap(SDL_Renderer* render)
{
	
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