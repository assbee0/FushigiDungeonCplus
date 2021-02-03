#include "MoveComponent.h"
#include "GameObject.h"
#include "Dungeon.h"
#include "BattleManager.h"
#include "Enemy.h"

MoveComponent::MoveComponent(GameObject* gameObject, bool isPlayer):
	Component(gameObject),
	mMapArray(nullptr),
	mDir(Vector2::Zero),
	mDst(Vector2::Zero),
	mIsMoving(false),
	mIsPlayer(isPlayer),
	mPixelsCount(0),
	mSpeed(200)
{
	mNumber = 2;
}

void MoveComponent::Update()
{
	if (mIsMoving)
	{
		MoveOneGrid();
	}
}

void MoveComponent::SetDir(Vector2 dir)
{
	if (mIsMoving)
		return;
	Vector2 curPos = mGameObject->GetPosition();
	mDir = dir;
	mDst = curPos + mDir * 32;
	if (WallCheck() && ColliderCheck())
	{
		mIsMoving = true;
		mGameObject->SetInputEnabled(false);
	}
}

void MoveComponent::MoveOneGrid()
{
	float realSpeed = mSpeed * Timer::deltaTime;
	Vector2 curPos = mGameObject->GetPosition();
	Vector2 tempPos = curPos + mDir * realSpeed;
	mPixelsCount += realSpeed;
	if (mPixelsCount < 32)
	{
		mGameObject->SetPosition(tempPos);
	}
	else
	{
		mGameObject->SetPosition(mDst);
		mDir = Vector2::Zero;
		mPixelsCount = 0;
		mIsMoving = false;

		if(mIsPlayer)
			mGameObject->GetGame()->GetDungeon()
				->GetComponent<BattleManager>()->NewTurn();

		mGameObject->SetInputEnabled(true);
	}
}

bool MoveComponent::WallCheck()
{
	int gridX = static_cast<int>(mDst.x / 32);
	int gridY = static_cast<int>(mDst.y / 32);
	int index = gridY * 40 + gridX;
	if (index > 1200 || index < 0)
		return false;
	if (mMapArray[index] == 0)
		return true;
	else
		return false;
}

bool MoveComponent::ColliderCheck()
{
	mEnemies = mGameObject->GetGame()->GetEnemies();
	for (auto enemy : mEnemies)
	{
		if (mDst == enemy->GetPosition())
			return false;
	}
	return true;
}