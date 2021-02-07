#pragma once
#include "Component.h"

class BattleManager : public Component
{
public:
	BattleManager(class GameObject* gameObject);
	void Update() override;
	void NewTurn();

private:
	int mTurnsCount;
	bool mIsInTurn;
};