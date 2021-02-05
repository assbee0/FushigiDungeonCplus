#include "MapComponent.h"
#include "GameObject.h"
#include "CameraLock.h"
#include "MapMaker.h"

MapComponent::MapComponent(GameObject* gameObject, Map* map):
	SpriteComponent(gameObject, 0),
	mMap(map),
	mMapArray(map->mapArray),
	mWidth(map->width),
	mHeight(map->height)
{

}

MapComponent::~MapComponent()
{
	delete mMap;
	mGameObject->RemoveComponent(this);
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
			if (mMapArray[i * mWidth + j] == 2)
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

void MapComponent::SetMap(Map* map)
{
	mMap = map; 
	mMapArray = mMap->mapArray; 
	mWidth = mMap->width; 
	mHeight = mMap->height;
}