#include "AnimeSprite.h"
#include "GameObject.h"
#include "CameraLock.h"
#include "Timer.h"

AnimeSprite::AnimeSprite(GameObject* gameObject, int drawOrder) :
	SpriteComponent(gameObject, drawOrder),
	mCurFrame(0.0f),
	mAnimeSpeed(2.0f)
{

}

void AnimeSprite::Draw(SDL_Renderer* renderer, CameraLock* cam)
{
	if (!mTexture)
		return;
	SDL_Rect srcrect = SDL_Rect();
	// The size of sprites should be 32 * 32 pixels
	srcrect.w = srcrect.h = 32;
	// An animation sprite contains more than one sprite, so take one of them
	if (mTexWidth > 32)
	{
		srcrect.x = static_cast<int>(mCurFrame) * 32;
		srcrect.y = 0;
	}

	SDL_Rect dstrect;
	dstrect.w = dstrect.h = 32;
	// Get the coordinate that should be drawed in the window
	Vector2 drawPos = cam->WorldToCamera(mGameObject->GetPosition());
	dstrect.x = static_cast<int>(drawPos.x);
	dstrect.y = static_cast<int>(drawPos.y);
	// Blit the sprite
	SDL_RenderCopyEx(renderer, mTexture, &srcrect, &dstrect, mGameObject->GetRotation(), nullptr, SDL_FLIP_NONE);

	// Go to next frame of this animation
	mCurFrame += mAnimeSpeed * Timer::deltaTime;
	float size = mTexWidth / 32.0f;
	// An animation is over, then back to the start
	while (mCurFrame >= size)
	{
		mCurFrame -= size;
	}
}

