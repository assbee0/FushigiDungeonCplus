#pragma once
#include "SpriteComponent.h"
#include <vector>

class MapComponent : public SpriteComponent
{
public:
	MapComponent(class GameObject* gameObject, int width, int height);

	void Draw(SDL_Renderer* renderer, class CameraLock* cam) override;
	void SetTexture(SDL_Texture* texture) override;

	int* GetMap() { return mMapArray; }
	int GetWidth() const { return mWidth * 32; }
	void SetWidth(int w) { mWidth = w; }
	int GetHeight() const { return mHeight * 32; }
	void SetHeight(int h) { mHeight = h; }

private:
	int* mMapArray;
	int mWidth;
	int mHeight;

	std::vector<SDL_Texture*> mTextures;
};