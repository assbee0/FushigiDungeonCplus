#pragma once
#include "SDL.h"
#include "Component.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(class GameObject* gameObject);
	~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	int GetTexWidth() const { return mTexWidth; }
	int GetTexHeight() const { return mTexHeight; }
	int GetDrawOrder() const { return mDrawOrder; }
	void SetDrawOrder(int order) { mDrawOrder = order; }

private:
	SDL_Texture* mTexture;
	int mTexWidth;
	int mTexHeight;
	int mDrawOrder;

};