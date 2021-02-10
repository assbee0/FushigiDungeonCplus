#pragma once
#include "BattleComponent.h"

class EnemyBattle : public BattleComponent
{
public:
	EnemyBattle(class GameObject* gameObject);
	void Update() override;

private:
	void BeAttacked(int damage) override;
	void AttackOver() override;
	class BattleComponent* CheckTarget() override;
};
