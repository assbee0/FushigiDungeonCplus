#include "MoveComponent.h"
#include "GameObject.h"
#include "Enemy.h"

MoveComponent::MoveComponent(GameObject* gameObject):
	Component(gameObject),
	mMapArray(nullptr),
	mDir(Vector2::Zero),
	mDst(Vector2::Zero),
	mIsMoving(false),
	mPixelsCount(0),
	mSpeed(200)
{

}

void MoveComponent::Update()
{
	if (mIsMoving)
	{
		MoveOneGrid();
	}
}

void MoveComponent::SetDir(Direction dir)
{
	if (mIsMoving)
		return;
	Vector2 curPos = mGameObject->GetPosition();
	switch (dir)
	{
	case MoveComponent::Direction::Up:
		mDir = Vector2::NY;
		break;
	case MoveComponent::Direction::Down:
		mDir = Vector2::Y;
		break;
	case MoveComponent::Direction::Left:
		mDir = Vector2::NX;
		break;
	case MoveComponent::Direction::Right:
		mDir = Vector2::X;
		break;
	default:
		mDir = Vector2::Zero;
		break;
	}
	mDst = curPos + mDir * 32;
	if (WallCheck() && ColliderCheck())
	{
		mIsMoving = true;
		mGameObject->SetInputEnabled(false);
	}
}

void MoveComponent::MoveOneGrid()
{
	float realSpeed = mSpeed * Time::deltaTime;
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
		mGameObject->SetInputEnabled(true);
	}
}

bool MoveComponent::WallCheck()
{
	int gridX = static_cast<int>(mDst.x / 32);
	int gridY = static_cast<int>(mDst.y / 32);
	int index = gridY * 20 + gridX;
	if (index > 300 || index < 0)
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