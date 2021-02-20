#pragma once
#include "BattleComponent.h"

class PlayerBattle : public BattleComponent
{
public:
	PlayerBattle(class GameObject* gameObject);
	void AttackTarget() override;
	void BeAttacked(int damage) override;
	void AttackOver() override;
	// Pick up health item and use it to recover current hp
	void RecoverHp(int curePercent);

private:
	// Check and process level up
	void LevelUp();
	// When player status changed, update the values in HUD
	void UpdateHUD();

	// Exp needed last level
	int mPreNeededExp;
};