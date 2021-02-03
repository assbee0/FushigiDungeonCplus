#include "MapComponent.h"
#include "GameObject.h"
#include "CameraLock.h"

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
	mNumber = 4;
}

void MapComponent::Draw(SDL_Renderer* renderer, CameraLock* cam)
{
	if (mTextures.size() != 2)
	{
		return;
	}
	SDL_Rect dstrect;
	dstrect.w = 32;
	dstrect.h = 32;
	Vector2 startPos = cam->CameraToWorld(Vector2::Zero);
	int startX = static_cast<int>(startPos.x / 32);
	int startY = static_cast<int>(startPos.y / 32);
	for (int i = startY; i < startY + 16; i++)
	{
		for (int j = startX; j < startX + 21; j++)
		{
			Vector2 worldPos = Vector2((float)j * 32, (float)i * 32);
			Vector2 camPos = cam->WorldToCamera(worldPos);
			dstrect.x = static_cast<int>(camPos.x);
			dstrect.y = static_cast<int>(camPos.y);
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