#include "SpriteComponent.h"
#include "GameObject.h"
#include "CameraLock.h"

SpriteComponent::SpriteComponent(GameObject* gameObject, int drawOrder):
	Component(gameObject),
	mTexture(nullptr),
	mTexWidth(0),
	mTexHeight(0),
	mDrawOrder(drawOrder)
{
	mGameObject->GetGame()->CreateSprite(this);
	mNumber = 1;
}

SpriteComponent::~SpriteComponent()
{
	mGameObject->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer, CameraLock* cam)
{
	if (!mTexture)
		return;
	SDL_Rect dstrect;
	dstrect.w = static_cast<int>(mTexWidth * mGameObject->GetScale().x);
	dstrect.h = static_cast<int>(mTexHeight * mGameObject->GetScale().y);
	Vector2 drawPos = cam->WorldToCamera(mGameObject->GetPosition());
	dstrect.x = static_cast<int>(drawPos.x);
	dstrect.y = static_cast<int>(drawPos.y);
	SDL_RenderCopyEx(renderer, mTexture, nullptr, &dstrect, mGameObject->GetRotation(), nullptr, SDL_FLIP_NONE);
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	//获取贴图的宽和高
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
