#include "Dungeon.h"
#include "Game.h"
#include "MapComponent.h"
#include "BattleManager.h"

Dungeon::Dungeon(Game* game): 
	GameObject(game)
{
	mMap = new MapComponent(this, 40, 30);
	mMap->SetTexture(game->GetTexture("Ground"));
	mMap->SetTexture(game->GetTexture("Wall"));

	bmc = new BattleManager(this);
	GetComponent<BattleManager>();
}

int* Dungeon::GetMap()
{
	return mMap->GetMap();
}