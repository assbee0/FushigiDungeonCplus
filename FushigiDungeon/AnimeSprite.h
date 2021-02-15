#pragma once
#include "SpriteComponent.h"
#include <vector>

class AnimeSprite : public SpriteComponent
{
public:
	AnimeSprite(class GameObject* gameObject, int drawOrder);
	void Draw(SDL_Renderer* renderer, class CameraLock* cam) override;

private:
	float mCurFrame;
	float mAnimeSpeed;
};