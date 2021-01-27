#pragma once
#include "SDL.h"
#include "SDL_image.h"

class Dungeon
{
public:
	Dungeon(SDL_Renderer* render);
	void CreateMap(SDL_Renderer* render);

	void SetTexture(SDL_Texture* tex) { mTexture = tex; }

private:
		
	int mMap[300];
	int mWidth;
	int mHeight;
	SDL_Texture* mTexture;
	SDL_Surface* Loading_Surf;
};