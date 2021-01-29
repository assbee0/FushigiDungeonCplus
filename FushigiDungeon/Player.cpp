#include "Player.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "BattleComponent.h"

Player::Player(Game *game):
	GameObject(game)
{
	SpriteComponent* ps = new SpriteComponent(this, 100);
	mc = new MoveComponent(this);
	bc = new BattleComponent(this);
	ps->SetTexture(game->GetTexture("Player"));
}

void Player::ProcessInput(const Uint8* state)
{
	if (!mInputEnabled)
		return;
	if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
	{
		mc->SetDir(MoveComponent::Direction::Up);
		bc->SetFacing(Vector2::NY);
	}
	else if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
	{
		mc->SetDir(MoveComponent::Direction::Down);
		bc->SetFacing(Vector2::Y);
	}
	else if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT])
	{
		mc->SetDir(MoveComponent::Direction::Left);
		bc->SetFacing(Vector2::NX);
	}
	else if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT])
	{
		mc->SetDir(MoveComponent::Direction::Right);
		bc->SetFacing(Vector2::X);
	}
	else if (state[SDL_SCANCODE_SPACE])
	{
		bc->SetBattling();
		mInputEnabled = false;
	}
}

void Player::Update()
{
	//printf("%f,%f\n", GetPosition().x, GetPosition().y);
	//printf("%d", mInputEnabled);
}