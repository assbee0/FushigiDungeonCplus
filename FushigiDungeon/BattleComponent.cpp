#include "BattleComponent.h"
#include "GameObject.h"
#include "Enemy.h"
#include "Timer.h"
#include "Random.h"

BattleComponent::BattleComponent(GameObject* gameObject):
	Component(gameObject),
	mTarget(nullptr),
	mFacing(Vector2::Y),
	mStartPos(Vector2::Zero),
	mIsBattling(false),
	mAnimeCount(0),
	mStatus(Status())
{

}

void BattleComponent::Update()
{
	if (mIsBattling)
	{
		AttackAnimation();
	}
}

bool BattleComponent::IsDead()
{
	if (mStatus.curHp <= 0)
		return true;
	else
		return false;
}

void BattleComponent::SetBattling()
{
	mIsBattling = true;
	mStartPos = mGameObject->GetPosition();

}

BattleComponent* BattleComponent::CheckTarget()
// Check if a target on current attack direction
{
	Vector2 curPos = mGameObject->GetPosition();
	Vector2 dstPos;
	// Facing grid
	dstPos = curPos + mFacing * 32;
	// Check if an enemy on facing grid
	std::vector<Enemy*> enemies = mGameObject->GetGame()->GetEnemies();
	for (auto enemy : enemies)
	{
		if (dstPos == enemy->GetPosition())
			return enemy->GetComponent<BattleComponent>();
	}
	return nullptr;
}

void BattleComponent::AttackTarget()
// Compute the attack damage
{
	int damage = mStatus.atk;
	mTarget->BeAttacked(damage);
}

void BattleComponent::BeAttacked(int damage)
// Receive damage and compute the real damage
{
	// Damage computation is attack - defense
	int realDamage = Mathf::Max(damage - mStatus.def, 0);
	// When attack <= defense, 50% to give 1 damage or 0 damage
	if (realDamage == 0)
	{
		realDamage = Random::GetIntRange(0, 1);
	}
	mStatus.curHp -= realDamage;
}

void BattleComponent::AttackAnimation()
{
	float animeSpeed = 150 * Timer::deltaTime;
	Vector2 curPos = mGameObject->GetPosition();
	Vector2 tempPos;
	mAnimeCount += animeSpeed;
	// Attack animation first part : Move one grid
	if (mAnimeCount < 32)
	{
		tempPos = curPos + mFacing * animeSpeed;
		mGameObject->SetPosition(tempPos);
	}
	// Attack animation second part : Return one grid to the start grid
	else if (mAnimeCount < 64)
	{
		tempPos = curPos - mFacing * animeSpeed;
		mGameObject->SetPosition(tempPos);
	}
	// Animation is over
	else
	{
		AttackOver();
	}
}

void BattleComponent::AttackOver()
{
	// Reset variables
	mGameObject->SetPosition(mStartPos);
	mIsBattling = false;
	mAnimeCount = 0;
	// Check if there is an enemy on the attacked grid
	mTarget = CheckTarget();
	if (mTarget)
	{
		AttackTarget();
		mTarget = nullptr;
	}
}

Status::Status():
	// Player's initial status
	level(1),
	curHp(10),
	maxHp(10),
	atk(2),
	def(1),
	exp(5)
{
	
}

void Status::Init(int lv, int cHp, int mHp, int a, int d, int e)
{
	level = lv;
	curHp = cHp;
	maxHp = mHp;
	atk = a;
	def = d;
	exp = e;
}
