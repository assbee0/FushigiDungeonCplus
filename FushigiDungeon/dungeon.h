#pragma once
#include "GameObject.h"

class Dungeon : public GameObject
{
public:
	Dungeon(class Game* game);

	int* GetMap();

private:
	class MapComponent* mMap;
};