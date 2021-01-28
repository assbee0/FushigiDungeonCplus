#pragma once
#include "SpriteComponent.h"
#include <vector>

class MapComponent : public SpriteComponent
{
public:
	MapComponent(class GameObject* gameObject, int width, int height);

	void Draw(SDL_Renderer* renderer) override;
	void SetTexture(SDL_Texture* texture) override;

	int* GetMap() { return mMapArray; }
	void SetWidth(int w) { mWidth = w; }
	void SetHeight(int h) { mHeight = h; }

private:
	int* mMapArray;
	int mWidth;
	int mHeight;

	std::vector<SDL_Texture*> mTextures;
};