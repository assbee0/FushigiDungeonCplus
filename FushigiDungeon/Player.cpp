#include "Player.h"
#include "Game.h"
#include "AnimeSprite.h"
#include "MoveComponent.h"
#include "PlayerBattle.h"

Player::Player(Game *game):
	GameObject(game)
{
	AnimeSprite* ps = new AnimeSprite(this, 100);
	mc = new MoveComponent(this);
	bc = new PlayerBattle(this);
	ps->SetTexture(game->GetTexture("Player"));
}

void Player::ProcessInput(const Uint8* state)
// Input from keyboard state
{
	// Player's will be freezed when the turn is not over
	if (!mInputEnabled)
		return;
	// Set player's direction from input
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
	// Press shift to accelerate the moving speed
	if (state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT])
	{
		mc->SetSpeed(400);
	}
	else
	{
		mc->SetSpeed(150);
	}
}

void Player::InputKeyPressed(int key)
// Input from keyboard pressed
{
	// Press space to attack
	if (key == SDLK_SPACE && mInputEnabled)
	{
		bc->SetBattling();
		mInputEnabled = false;
	}
}
