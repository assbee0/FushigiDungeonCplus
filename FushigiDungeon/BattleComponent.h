#pragma once
#include "Component.h"
#include "Math.h"

class BattleComponent : public Component
{
public:
	BattleComponent(class GameObject* gameObject, bool isPlayer);
	void Update() override;

	void SetFacing(Vector2 f) { mFacing = f; }
	bool GetBattling() const { return mIsBattling; }
	void SetBattling();

protected:
	virtual class BattleComponent* CheckTarget();
	void AttackTarget();
	void BeAttacked(int damage);
	void AttackAnimation();
	virtual void AttackOver();

	bool mIsPlayer;
	class BattleComponent* mTarget;
	Vector2 mFacing;
	Vector2 mStartPos;
	bool mIsBattling;
	float mAnimeCount;

	int mHp;
	int mAttack;
};