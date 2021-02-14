#include "Player.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "PlayerBattle.h"

Player::Player(Game *game):
	GameObject(game)
{
	SpriteComponent* ps = new SpriteComponent(this, 100);
	mc = new MoveComponent(this, true);
	bc = new PlayerBattle(this);
	ps->SetTexture(game->GetTexture("Player"));
}

void Player::ProcessInput(const Uint8* state)
{
	if (!mInputEnabled)
		return;
	if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
	{
		mc->SetDir(Vector2::NY);
		bc->SetFacing(Vector2::NY);
	}
	else if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
	{
		mc->SetDir(Vector2::Y);
		bc->SetFacing(Vector2::Y);
	}
	else if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT])
	{
		mc->SetDir(Vector2::NX);
		bc->SetFacing(Vector2::NX);
	}
	else if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT])
	{
		mc->SetDir(Vector2::X);
		bc->SetFacing(Vector2::X);
	}
}

void Player::InputKeyPressed(int key)
{
	if (key == SDLK_SPACE && mInputEnabled)
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

