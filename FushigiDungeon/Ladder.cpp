#include "Game.h"
#include "SpriteComponent.h"
#include "Ladder.h"

Ladder::Ladder(Game* game):
	GameObject(game)
{
	SpriteComponent* sc = new SpriteComponent(this, 98);
	sc->SetTexture(game->GetTexture("Ladder"));
}