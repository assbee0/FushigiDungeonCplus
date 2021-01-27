#include "Player.h"
#include "Game.h"
#include "SpriteComponent.h"

Player::Player(Game *game):
	GameObject(game),
	mIsWalking(false),
	mVec(Vector2::Zero),
	mPos(Vector2::Zero),
	mDst(Vector2::Zero),
	mPixelsCount(0)
{
	SpriteComponent* ps = new SpriteComponent(this);
	ps->SetTexture(game->GetTexture("Player"));
}

void Player::ProcessInput(const Uint8* state)
{
	if (!mIsWalking)
	{
		mPos = GetPosition();
		if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
		{
			mVec.y = (int)(-PLAYER_SPEED * Time::deltaTime);
			mDst = Vector2::Sum(mPos, Vector2(0, -32));
			mIsWalking = true;
		}
		else if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
		{
			mVec.y = (int)(PLAYER_SPEED * Time::deltaTime);
			mDst = Vector2::Sum(mPos, Vector2(0, 32));
			mIsWalking = true;
		}
		else if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT])
		{
			mVec.x = (int)(-PLAYER_SPEED * Time::deltaTime);
			mDst = Vector2::Sum(mPos, Vector2(-32, 0));
			mIsWalking = true;
		}
		else if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT])
		{
			mVec.x = (int)(PLAYER_SPEED * Time::deltaTime);
			mDst = Vector2::Sum(mPos, Vector2(32, 0));
			mIsWalking = true;
		}
	}
}

void Player::Update()
{
	if (mIsWalking)
	{
		Vector2 tempPos;
		tempPos = Vector2::Sum(GetPosition(), mVec);
		mPixelsCount += PLAYER_SPEED * Time::deltaTime;
		if (mPixelsCount < 32)
		{
			SetPosition(tempPos);
		}
		else
		{
			SetPosition(mDst);
			mIsWalking = false;
			mVec = Vector2::Zero;
			mPixelsCount = 0;
		}
	}
}