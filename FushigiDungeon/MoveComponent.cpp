#include "MoveComponent.h"
#include "GameObject.h"
#include "BattleManager.h"
#include "Enemy.h"
#include "Timer.h"
#include "Dungeon.h"
#include "MapMaker.h"
#include "Ladder.h"
#include "MessageBox.h"
#include "HealthItem.h"
#include "PlayerBattle.h"

MoveComponent::MoveComponent(GameObject* gameObject):
	Component(gameObject),
	mMap(nullptr),
	mDir(Vector2::Zero),
	mDst(Vector2::Zero),
	mIsMoving(false),
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
// Set the moving direction, if no obstacle, start moving
{
	// Can only be called at idle state
	if (mIsMoving)
		return;
	Vector2 curPos = mGameObject->GetPosition();
	mDir = dir;
	// Destination grid on current direction
	Vector2 tempDst = curPos + mDir * 32;
	// Check if there is a wall or other obstacle
	if (WallCheck(mDir) && ColliderCheck(mDir))
	{
		// Set destination and start moving
		mDst = tempDst;
		mIsMoving = true;
		// Disable the input for player
		mGameObject->SetInputEnabled(false);
		// Start a new turn
		mGameObject->GetGame()->GetDungeon()
			->GetComponent<BattleManager>()->NewTurn();
	}
}

void MoveComponent::MoveOneGrid()
// Move from a grid to an adjacent grid
{
	// Speed for real time, not affected by frame rate
	float realSpeed = mSpeed * Timer::deltaTime;
	Vector2 curPos = mGameObject->GetPosition();
	// Temporary position during moving
	Vector2 tempPos = curPos + mDir * realSpeed;
	mPixelsCount += realSpeed;
	// Have not moved a complete grid
	if (mPixelsCount < 32)
	{
		mGameObject->SetPosition(tempPos);
	}
	// Have moved 32 pixels, which means reach the destination
	else
	{
		ReachOneGrid();
	}
}

bool MoveComponent::WallCheck(Vector2 dir)
// Check if there is a wall at the direction dir
{
	Vector2 tempDst = mGameObject->GetPosition() + dir * 32;
	int gridX = static_cast<int>(tempDst.x / 32);
	int gridY = static_cast<int>(tempDst.y / 32);
	// Calculate the 1-d index from the coordinate
	int index = gridY * (mMap->width) + gridX;
	// Out of the map
	if (index > ((mMap->width) * (mMap->height)) || index < 0)
		return false;
	// 2 in mapArray means able to walk through
	if (mMap->mapArray[index] == 2)
		return true;
	else
		return false;
}

bool MoveComponent::ColliderCheck(Vector2 dir)
// Check if there is an enemy at the direction dir
{
	Vector2 tempDst = mGameObject->GetPosition() + dir * 32;
	mEnemies = mGameObject->GetGame()->GetEnemies();
	// Check all the enemies' position
	for (auto enemy : mEnemies)
	{
		if (tempDst == enemy->GetPosition())
			return false;
	}
	return true;
}

void MoveComponent::ReachOneGrid()
// Have completed one grid's move, interact with the objects on the destination
{
	// Ensure this move will be 32 pixels
	mGameObject->SetPosition(mDst);
	// Reset variables
	mDir = Vector2::Zero;
	mPixelsCount = 0;
	mIsMoving = false;

	// Interact with ladder
	if (mDst == mGameObject->GetGame()->GetLadder()->GetPosition())
	{
		new MessageBox(mGameObject->GetGame());
	}
	// Interact with health item
	HealthItem* hItem = mGameObject->GetGame()->GetHealthItem();
	if (hItem != nullptr)
	{
		if (mDst == hItem->GetPosition())
		{
			int percent = mGameObject->GetGame()->GetHealthItem()->GetPercent();
			// Recover player's hp
			mGameObject->GetComponent<PlayerBattle>()->RecoverHp(percent);
			// Destory this item
			hItem->SetState(GameObject::State::EDead);
		}
	}

}