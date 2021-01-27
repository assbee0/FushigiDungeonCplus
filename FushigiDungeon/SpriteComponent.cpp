#include "SpriteComponent.h"
#include "GameObject.h"
SpriteComponent::SpriteComponent(GameObject* gameObject):
	Component(gameObject),
	mTexture(nullptr),
	mTexWidth(0),
	mTexHeight(0),
	mDrawOrder(100)
{
	mGameObject->GetGame()->CreateSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mGameObject->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (!mTexture)
		return;
	SDL_Rect dstrect;
	dstrect.w = static_cast<int>(mTexWidth * mGameObject->GetScale().x);
	dstrect.h = static_cast<int>(mTexHeight * mGameObject->GetScale().y);
	dstrect.x = static_cast<int>(mGameObject->GetPosition().x - dstrect.w/2);
	dstrect.y = static_cast<int>(mGameObject->GetPosition().y - dstrect.h/2);
	SDL_RenderCopyEx(renderer, mTexture, nullptr, &dstrect, mGameObject->GetRotation(), nullptr, SDL_FLIP_NONE);
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	//获取贴图的宽和高
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
