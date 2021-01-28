#include "MapComponent.h"
#include "GameObject.h"

MapComponent::MapComponent(GameObject* gameObject, int width, int height):
	SpriteComponent(gameObject, 0),
	mWidth(width),
	mHeight(height)
{
	mMapArray = new int[width * height]();
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int index = i * width + j;
			if (i < 3 || i > 11 || j < 3 || j > 16)
				mMapArray[index] = 1;
			else
				mMapArray[index] = 0;
			if (j > 7 && j < 12)
				mMapArray[index] = 0;
		}
	}
}

void MapComponent::Draw(SDL_Renderer* renderer)
{
	if (mTextures.size() != 2)
	{
		return;
	}
	SDL_Rect dstrect;
	dstrect.w = 32;
	dstrect.h = 32;
	for (int i = 0; i < mHeight; i++)
	{
		for (int j = 0; j < mWidth; j++)
		{
			dstrect.x = j * 32;
			dstrect.y = i * 32;
			if (mMapArray[i * mWidth + j] == 0)
				SDL_RenderCopy(renderer, mTextures[0], nullptr, &dstrect);
			else
				SDL_RenderCopy(renderer, mTextures[1], nullptr, &dstrect);
		}
	}
}

void MapComponent::SetTexture(SDL_Texture* texture)
{
	mTextures.emplace_back(texture);
}