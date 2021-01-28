#include "Player.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"

Player::Player(Game *game):
	GameObject(game),
	mIsWalking(false),
	mVec(Vector2::Zero),
	mPos(Vector2::Zero),
	mDst(Vector2::Zero),
	mPixelsCount(0)
{
	SpriteComponent* ps = new SpriteComponent(this, 100);
	mc = new MoveComponent(this);
	ps->SetTexture(game->GetTexture("Player"));
}

void Player::ProcessInput(const Uint8* state)
{
	if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
	{
		mc->SetDir(MoveComponent::Direction::Up);
	}
	else if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
	{
		mc->SetDir(MoveComponent::Direction::Down);
	}
	else if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT])
	{
		mc->SetDir(MoveComponent::Direction::Left);
	}
	else if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT])
	{
		mc->SetDir(MoveComponent::Direction::Right);
	}
}

void Player::Update()
{
	
}

void Player::SetMap(int* map)
{
	mc->SetMap(map);
}