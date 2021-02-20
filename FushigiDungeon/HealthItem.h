#pragma once
#include "GameObject.h"

class HealthItem : public GameObject
{
public:
	HealthItem(class Game* game, int number);
	~HealthItem();

	int GetPercent() const { return mPercent; }

private:
	int mNumber;
	// Health percent of max hp
	int mPercent;
};