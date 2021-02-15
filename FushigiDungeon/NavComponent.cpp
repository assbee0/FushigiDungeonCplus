#include "NavComponent.h"
#include "Random.h"
#include "Player.h"
#include "MapMaker.h"
#include "Enemy.h"

NavComponent::NavComponent(GameObject* gameObject):
	MoveComponent(gameObject, false),
	mPlayer(nullptr)
{

}

void NavComponent::Update()
{
	MoveComponent::Update();
	mSpeed = mPlayer->GetComponent<MoveComponent>()->GetSpeed();
}

void NavComponent::Wander()
{
	std::vector<Vector2> dirs;
	if (CheckAllCollider(Vector2::NY))
		dirs.emplace_back(Vector2::NY);
	if (CheckAllCollider(Vector2::Y))
		dirs.emplace_back(Vector2::Y);
	if (CheckAllCollider(Vector2::X))
		dirs.emplace_back(Vector2::X);
	if (CheckAllCollider(Vector2::NX))
		dirs.emplace_back(Vector2::NX);

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

void NavComponent::Chase()
{
	Vector2 curPos = mGameObject->GetPosition();
	Vector2 playerPos = mPlayer->GetPosition();
	
	std::vector<Vector2> dirs;
	Vector2 dir;
	if (playerPos.y < curPos.y && CheckAllCollider(Vector2::NY))
		dirs.emplace_back(Vector2::NY);
	else if(playerPos.y > curPos.y && CheckAllCollider(Vector2::Y))
		dirs.emplace_back(Vector2::Y);

	if (playerPos.x < curPos.x && CheckAllCollider(Vector2::NX))
		dirs.emplace_back(Vector2::NX);
	else if (playerPos.x > curPos.x && CheckAllCollider(Vector2::X))
		dirs.emplace_back(Vector2::X);

	if (dirs.empty())
		mDir = Vector2::Zero;
	else
	{
		int index = Random::GetIntRange(0, dirs.size() - 1);
		mDir = dirs[index];
		mDst = curPos + mDir * 32;
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
	Vector2 sub = mGameObject->GetPosition() - mPlayer->GetComponent<MoveComponent>()->GetDst();
	return static_cast<int>((Mathf::Abs(sub.x) + Mathf::Abs(sub.y)) / 32);
}

bool NavComponent::GetPlayerMoving()
{
	return mPlayer->GetComponent<MoveComponent>()->GetIsMoving();
}

bool NavComponent::CheckAllCollider(Vector2 dir)
{
	bool check = WallCheck(dir) && ColliderCheck(dir);
	Vector2 tempDst = mGameObject->GetPosition() + dir * 32;
	if (tempDst == mPlayer->GetComponent<MoveComponent>()->GetDst())
		return false;

	for (auto enemy : mGameObject->GetGame()->GetEnemies())
	{
		NavComponent* eNav = enemy->GetComponent<NavComponent>();
		if (eNav->GetIsMoving())
		{
			if (tempDst == eNav->GetDst())
				return false;
		}
	}
	return check;
}