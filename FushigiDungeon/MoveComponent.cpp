#include "MoveComponent.h"
#include "GameObject.h"
#include "BattleManager.h"
#include "Enemy.h"
#include "Timer.h"
#include "Dungeon.h"
#include "MapMaker.h"
#include "Ladder.h"

MoveComponent::MoveComponent(GameObject* gameObject, bool isPlayer):
	Component(gameObject),
	mMap(nullptr),
	mDir(Vector2::Zero),
	mDst(Vector2::Zero),
	mIsMoving(false),
	mIsPlayer(isPlayer),
	mPixelsCount(0),
	mSpeed(150)
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
	Vector2 tempDst = curPos + mDir * 32;
	if (WallCheck(mDir) && ColliderCheck(mDir))
	{
		mDst = tempDst;
		mIsMoving = true;
		mGameObject->SetInputEnabled(false);

		mGameObject->GetGame()->GetDungeon()
			->GetComponent<BattleManager>()->NewTurn();
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
		ReachOneGrid();
	}
}

bool MoveComponent::WallCheck(Vector2 dir)
{
	Vector2 tempDst = mGameObject->GetPosition() + dir * 32;
	int gridX = static_cast<int>(tempDst.x / 32);
	int gridY = static_cast<int>(tempDst.y / 32);
	int index = gridY * (mMap->width) + gridX;
	if (index > ((mMap->width) * (mMap->height)) || index < 0)
		return false;
	if (mMap->mapArray[index] == 2)
		return true;
	else
		return false;
}

bool MoveComponent::ColliderCheck(Vector2 dir)
{
	Vector2 tempDst = mGameObject->GetPosition() + dir * 32;
	mEnemies = mGameObject->GetGame()->GetEnemies();
	for (auto enemy : mEnemies)
	{
		if (tempDst == enemy->GetPosition())
			return false;
	}
	return true;
}

void MoveComponent::ReachOneGrid()
{
	mGameObject->SetPosition(mDst);
	mDir = Vector2::Zero;
	mPixelsCount = 0;
	mIsMoving = false;

	if (mIsPlayer)
	{
		if (mDst == mGameObject->GetGame()->GetLadder()->GetPosition())
		{
			mGameObject->GetGame()->NewFloor();
		}
	}

	//mGameObject->SetInputEnabled(true);
}