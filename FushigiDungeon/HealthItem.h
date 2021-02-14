#pragma once
#include "GameObject.h"

class HealthItem : public GameObject
{
public:
	HealthItem(class Game* game, int number);
	~HealthItem();

	int PercentHealth(int maxHp);
	int GetPercent() const { return mPercent; }

private:
	int mNumber;
	int mPercent;
};