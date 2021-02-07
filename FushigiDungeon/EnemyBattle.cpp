#include "EnemyBattle.h"
#include "GameObject.h"
#include "Player.h"

EnemyBattle::EnemyBattle(GameObject* gameObject):
	BattleComponent(gameObject, false)
{
	mHp = 5;
}

void EnemyBattle::Update()
{
	if (mIsBattling)
	{
		CheckTarget();
		if (mTarget)
			AttackAnimation();
	}
}

bool EnemyBattle::IsDead()
{
	if (mHp <= 0)
		return true;
	else
		return false;
}

void EnemyBattle::AttackOver()
{
	mGameObject->SetPosition(mStartPos);
	mIsBattling = false;
	mAnimeCount = 0;

	if (mTarget)
	{
		AttackTarget();
		mTarget = nullptr;
	}
}

BattleComponent* EnemyBattle::CheckTarget()
{
	Vector2 curPos = mGameObject->GetPosition();
	Player* player = mGameObject->GetGame()->GetPlayer();
	mTarget = player->GetComponent<BattleComponent>();
	if(player->GetPosition() - curPos == Vector2(0, 32))
	{
		mFacing = Vector2::Y;
		return mTarget;
	}
	else if (player->GetPosition() - curPos == Vector2(0, -32))
	{
		mFacing = Vector2::NY;
		return mTarget;
	}
	else if (player->GetPosition() - curPos == Vector2(32, 0))
	{
		mFacing = Vector2::X;
		return mTarget;
	}
	else if (player->GetPosition() - curPos == Vector2(-32, 0))
	{
		mFacing = Vector2::NX;
		return mTarget;
	}
	return nullptr;
}