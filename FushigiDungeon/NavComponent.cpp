#include "NavComponent.h"
#include "Random.h"
#include "Player.h"

NavComponent::NavComponent(GameObject* gameObject):
	MoveComponent(gameObject, false),
	mPlayer(nullptr)
{

}

void NavComponent::Wander()
{
	std::vector<Vector2> dirs;

	mDir = Vector2(0, -1);
	if (WallCheck())
		dirs.emplace_back(mDir);
	mDir = Vector2(0, 1);
	if (WallCheck())
		dirs.emplace_back(mDir);
	mDir = Vector2(1, 0);
	if (WallCheck())
		dirs.emplace_back(mDir);
	mDir = Vector2(-1, 0);
	if (WallCheck())
		dirs.emplace_back(mDir);

	if (dirs.empty())
		mDir = Vector2::Zero;
	else
	{
		int index = Random::GetIntRange(0, dirs.size() - 1);
		mDir = dirs[index];
		mDst = mGameObject->GetPosition() + mDir * 32;
		mIsMoving = true;
	}
}

void NavComponent::ReachOneGrid()
{
	mGameObject->SetPosition(mDst);
	mDir = Vector2::Zero;
	mPixelsCount = 0;
	mIsMoving = false;
}

int NavComponent::PlayerDistance()
{
	Vector2 sub = mGameObject->GetPosition() - mPlayer->GetPosition();
	return static_cast<int>((Mathf::Abs(sub.x) + Mathf::Abs(sub.y)) / 32);
}