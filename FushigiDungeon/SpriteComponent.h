#pragma once
#include "SDL.h"
#include "Component.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(class GameObject* gameObject, int drawOrder);
	~SpriteComponent();

	// Draw map according to the camera position
	virtual void Draw(SDL_Renderer* renderer, class CameraLock* cam);
	// Set the sprite to this component
	virtual void SetTexture(SDL_Texture* texture);

	int GetTexWidth() const { return mTexWidth; }
	int GetTexHeight() const { return mTexHeight; }
	int GetDrawOrder() const { return mDrawOrder; }
	void SetDrawOrder(int order) { mDrawOrder = order; }

protected:
	int mDrawOrder;
	SDL_Texture* mTexture;
	int mTexWidth;
	int mTexHeight;

};