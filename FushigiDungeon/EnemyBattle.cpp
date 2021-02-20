#include "EnemyBattle.h"
#include "GameObject.h"
#include "Player.h"
#include "MoveComponent.h"

EnemyBattle::EnemyBattle(GameObject* gameObject, Status status):
	BattleComponent(gameObject)
{
	mStatus = status;
}

void EnemyBattle::Update()
{
	Player* player = mGameObject->GetGame()->GetPlayer();
	bool pIsMoving = player->GetComponent<MoveComponent>()->GetIsMoving();
	// If player is moving to the adjacent grid, wait until player's move is over
	if (mIsBattling && !pIsMoving)
	{
		// Enemy is different from player, the facing direction should be the player's position
		// So the target should be checked before attacking
		CheckTarget();
		if (mTarget)
			AttackAnimation();
	}
}

void EnemyBattle::AttackOver()
{
	// Reset variables
	mGameObject->SetPosition(mStartPos);
	mIsBattling = false;
	mAnimeCount = 0;

	if (mTarget)
	{
		// Attack and compute the damage
		AttackTarget();
		mTarget = nullptr;
		Mix_PlayChannel(-1, mGameObject->GetGame()->GetSound("Attack2"), 0);
	}
}

BattleComponent* EnemyBattle::CheckTarget()
// Return the target object, and decide the facing direction
{
	Vector2 curPos = mGameObject->GetPosition();
	Player* player = mGameObject->GetGame()->GetPlayer();
	mTarget = player->GetComponent<BattleComponent>();
	// Player's destination position, not current position
	Vector2 playerDst = player->GetComponent<MoveComponent>()->GetDst();
	// Four directions depending on enemy's position and player's dst position
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
