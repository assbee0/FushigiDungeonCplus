#pragma once
#include "GameObject.h"
#include <string>
#include "EnemyBattle.h"

class Enemy : public GameObject
{
public:
	Enemy(class Game* game, int number);
	~Enemy();

private:
	bool LoadData(const std::string& fileName, int number);

	int mNumber;
	std::string mName;
	class Status mStatus;
};