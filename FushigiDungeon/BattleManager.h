#pragma once
#include "Component.h"

class BattleManager : public Component
{
public:
	BattleManager(class GameObject* gameObject);
	void Update() override;

	// When player takes action, this method is called to start a new turn
	void NewTurn();

private:
	int mTurnsCount;
	bool mIsInTurn;
};