#include "Dungeon.h"
#include "Game.h"
#include "MapComponent.h"
#include "BattleManager.h"
#include "MapMaker.h"
#include "GameClearUI.h"

Dungeon::Dungeon(Game* game): 
	GameObject(game),
	mFloor(1),
	mWidth(20),
	mHeight(15),
	mMap(nullptr)
{
	MapMaker* mapMaker = new MapMaker(this, mWidth, mHeight, 10, 10);
	mMap = mapMaker->BuildMap();

	MapComponent* mc = new MapComponent(this, mMap);
	mc->SetTexture(game->GetTexture("Ground"));
	mc->SetTexture(game->GetTexture("Wall"));

	BattleManager* bmc = new BattleManager(this);
}

void Dungeon::NewFloor()
{
	// Free last map
	delete mMap->mapArray;
	delete mMap;

	// The map is getting bigger than last floor
	mWidth = Mathf::Min(20 + mFloor * 2, 60);
	mHeight = Mathf::Min(15 + mFloor * 2, 55);
	// Make new map
	GetComponent<MapMaker>()->SetParameters(mWidth, mHeight, 10, 10);
	mMap = GetComponent<MapMaker>()->BuildMap();
	GetComponent<MapComponent>()->SetMap(mMap);
	mFloor++;
	printf("Floor %d\n", mFloor);
	
	// Change bgm or set game clear for some specific floors
	switch (mFloor)
	{
	case 6:
		Mix_PlayMusic(GetGame()->GetMusic("Dungeon2"), -1);
		break;
	case 12:
		Mix_PlayMusic(GetGame()->GetMusic("Dungeon3"), -1);
		break;
	case 18:
		Mix_PlayMusic(GetGame()->GetMusic("Dungeon4"), -1);
		break;
	case 20:
		Mix_PlayMusic(GetGame()->GetMusic("Victory"), -1);
		new GameClearUI(GetGame());
		break;
	default:
		break;
	}
}