#include "BattleComponent.h"
#include "GameObject.h"
#include "Dungeon.h"
#include "Enemy.h"
#include "BattleManager.h"

BattleComponent::BattleComponent(GameObject* gameObject, bool isPlayer):
	Component(gameObject),
	mIsPlayer(isPlayer),
	mTarget(nullptr),
	mFacing(Vector2::Zero),
	mStartPos(Vector2::Zero),
	mIsBattling(false),
	mAnimeCount(0),
	mHp(10),
	mAttack(2)
{
	mNumber = 3;
}

void BattleComponent::Update()
{
	if (mIsBattling)
	{
		AttackAnimation();
	}
}

void BattleComponent::SetBattling()
{
	mIsBattling = true;
	mStartPos = mGameObject->GetPosition();

	if (mIsPlayer)
	{
	}
}

Enemy* BattleComponent::CheckTarget()
{
	Vector2 curPos = mGameObject->GetPosition();
	Vector2 dstPos;
	dstPos = curPos + mFacing * 32;
	std::vector<Enemy*> enemies = mGameObject->GetGame()->GetEnemies();
	for (auto enemy : enemies)
	{
		if (dstPos == enemy->GetPosition())
			return enemy;
	}
	return nullptr;
}

void BattleComponent::AttackTarget()
{
	int damage = mAttack;
	mTarget->BeAttacked(damage);
}

void BattleComponent::AttackAnimation()
{
	float animeSpeed = 150 * Timer::deltaTime;
	Vector2 curPos = mGameObject->GetPosition();
	Vector2 tempPos;
	mAnimeCount += animeSpeed;
	if (mAnimeCount < 32)
	{
		tempPos = curPos + mFacing * animeSpeed;
		mGameObject->SetPosition(tempPos);
	}
	else if (mAnimeCount < 64)
	{
		tempPos = curPos - mFacing * animeSpeed;
		mGameObject->SetPosition(tempPos);
	}
	else
	{
		mGameObject->SetPosition(mStartPos);
		mIsBattling = false;
		mAnimeCount = 0;

		mTarget = CheckTarget();
		if (mTarget)
		{
			AttackTarget();
			mTarget = nullptr;
		}

		mGameObject->GetGame()->GetDungeon()
			->GetComponent<BattleManager>()->NewTurn();

		mGameObject->SetInputEnabled(true);
	}
}