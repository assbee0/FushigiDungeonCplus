#include "EnemyBattle.h"
#include "GameObject.h"
#include "Player.h"
#include "MoveComponent.h"

EnemyBattle::EnemyBattle(GameObject* gameObject):
	BattleComponent(gameObject, false)
{
	mStatus.Init(1, 3, 3, 2, 0, 2);
}

void EnemyBattle::Update()
{
	Player* player = mGameObject->GetGame()->GetPlayer();
	bool pIsMoving = player->GetComponent<MoveComponent>()->GetIsMoving();
	if (mIsBattling && !pIsMoving)
	{
		CheckTarget();
		if (mTarget)
			AttackAnimation();
	}
}

void EnemyBattle::BeAttacked(int damage)
{
	mStatus.curHp -= damage;
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
	Vector2 playerDst = player->GetComponent<MoveComponent>()->GetDst();
	if(playerDst - curPos == Vector2(0, 32))
	{
		mFacing = Vector2::Y;
		return mTarget;
	}
	else if (playerDst - curPos == Vector2(0, -32))
	{
		mFacing = Vector2::NY;
		return mTarget;
	}
	else if (playerDst - curPos == Vector2(32, 0))
	{
		mFacing = Vector2::X;
		return mTarget;
	}
	else if (playerDst - curPos == Vector2(-32, 0))
	{
		mFacing = Vector2::NX;
		return mTarget;
	}
	return nullptr;
}
