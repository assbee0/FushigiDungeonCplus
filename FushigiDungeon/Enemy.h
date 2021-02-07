#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy(class Game* game);
	~Enemy();
};