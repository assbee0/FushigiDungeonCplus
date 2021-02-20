#pragma once
#include "SpriteComponent.h"
#include <vector>

class MapComponent : public SpriteComponent
{
public:
	MapComponent(class GameObject* gameObject, class Map* map);
	~MapComponent();

	// Draw map according to the camera position
	void Draw(SDL_Renderer* renderer, class CameraLock* cam) override;
	// Add the map tile sprite
	void SetTexture(SDL_Texture* texture) override;

	int* GetMap() { return mMapArray; }
	void SetMap(class Map* map);
	int GetWidth() const { return mWidth * 32; }
	void SetWidth(int w) { mWidth = w; }
	int GetHeight() const { return mHeight * 32; }
	void SetHeight(int h) { mHeight = h; }

private:
	class Map* mMap;
	int* mMapArray;
	int mWidth;
	int mHeight;

	std::vector<SDL_Texture*> mTextures;
};