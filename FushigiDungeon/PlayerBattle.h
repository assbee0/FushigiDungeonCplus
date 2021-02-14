#pragma once
#include "BattleComponent.h"

class PlayerBattle : public BattleComponent
{
public:
	PlayerBattle(class GameObject* gameObject);
	void AttackTarget() override;
	void BeAttacked(int damage) override;
	void AttackOver() override;
	void RecoverHp(int curePercent);

private:
	void LevelUp();
	void UpdateHUD();

	int mPreNeededExp;
};