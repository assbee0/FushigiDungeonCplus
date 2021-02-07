#pragma once
#include "BattleComponent.h"

class EnemyBattle : public BattleComponent
{
public:
	EnemyBattle(class GameObject* gameObject);
	void Update() override;
	bool IsDead();

private:
	void AttackOver() override;
	class BattleComponent* CheckTarget() override;
};