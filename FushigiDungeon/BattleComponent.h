#pragma once
#include "Component.h"
#include "Math.h"

class BattleComponent : public Component
{
public:
	BattleComponent(class GameObject* gameObject, bool isPlayer);
	void Update() override;

	void SetFacing(Vector2 f) { mFacing = f; }
	void SetBattling();

private:
	class Enemy* CheckTarget();
	void AttackTarget();
	void AttackAnimation();

	bool mIsPlayer;
	class Enemy* mTarget;
	Vector2 mFacing;
	Vector2 mStartPos;
	bool mIsBattling;
	float mAnimeCount;

	int mHp;
	int mAttack;
};