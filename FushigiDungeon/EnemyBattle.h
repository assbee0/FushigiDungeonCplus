#pragma once
#include "BattleComponent.h"

class EnemyBattle : public BattleComponent
{
public:
	EnemyBattle(class GameObject* gameObject, class Status status);
	void Update() override;

private:
	void AttackOver() override;
	class BattleComponent* CheckTarget() override;
};
