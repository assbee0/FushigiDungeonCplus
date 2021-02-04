#include "Dungeon.h"
#include "Game.h"
#include "MapComponent.h"
#include "BattleManager.h"
#include "MapMaker.h"

Dungeon::Dungeon(Game* game): 
	GameObject(game)
{
	MapMaker* mapMaker = new MapMaker(this);
	mapMaker->BuildMap();

	mMap = new MapComponent(this, 20, 15);
	mMap->SetMap(mapMaker->GetMap());
	mMap->SetTexture(game->GetTexture("Ground"));
	mMap->SetTexture(game->GetTexture("Wall"));

	bmc = new BattleManager(this);
	GetComponent<BattleManager>();
}

int* Dungeon::GetMap()
{
	return mMap->GetMap();
}