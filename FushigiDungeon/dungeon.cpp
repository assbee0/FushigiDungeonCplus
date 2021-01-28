#include "Dungeon.h"
#include "Game.h"
#include "MapComponent.h"

Dungeon::Dungeon(Game* game):
	GameObject(game)
{
	mMap = new MapComponent(this, 20, 15);
	mMap->SetTexture(game->GetTexture("Ground"));
	mMap->SetTexture(game->GetTexture("Wall"));
}

int* Dungeon::GetMap()
{
	return mMap->GetMap();
}