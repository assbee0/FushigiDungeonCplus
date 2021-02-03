#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy(class Game* game);
	~Enemy();
	void BeAttacked(int damage);


private:
	class MoveComponent* mc;
	int mHp;
};