#pragma once
#include "Component.h"
#include "Math.h"

class Status
{
public:
	Status();
	void Init(int lv, int cHp, int mHp, int a, int d, int e);

	int level;
	int curHp;
	int maxHp;
	int atk;
	int def;
	int exp;
};

class BattleComponent : public Component
{
public:
	BattleComponent(class GameObject* gameObject, bool isPlayer);
	void Update() override;

	bool IsDead();
	void SetFacing(Vector2 f) { mFacing = f; }
	bool GetBattling() const { return mIsBattling; }
	void SetBattling();
	int GetExp() const { return mStatus.exp; }

protected:
	virtual class BattleComponent* CheckTarget();
	void AttackTarget();
	virtual void BeAttacked(int damage);
	void AttackAnimation();
	virtual void AttackOver();

	bool mIsPlayer;
	class BattleComponent* mTarget;
	Vector2 mFacing;
	Vector2 mStartPos;
	bool mIsBattling;
	float mAnimeCount;
	
	class Status mStatus;

private:
	void UpdateHUD();
};
