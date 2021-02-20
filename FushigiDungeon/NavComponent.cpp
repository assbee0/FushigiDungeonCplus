#include "NavComponent.h"
#include "Random.h"
#include "Player.h"
#include "MapMaker.h"
#include "Enemy.h"

NavComponent::NavComponent(GameObject* gameObject):
	MoveComponent(gameObject),
	mPlayer(nullptr)
{

}

void NavComponent::Update()
{
	MoveComponent::Update();
	// Always have the same moving speed with player
	mSpeed = mPlayer->GetComponent<MoveComponent>()->GetSpeed();
}

void NavComponent::Wander()
// When player is far from the enemy, wander
{
	// Use for storing all the directions that can move
	std::vector<Vector2> dirs;
	// Add the directions that can move
	if (CheckAllCollider(Vector2::NY))
		dirs.emplace_back(Vector2::NY);
	if (CheckAllCollider(Vector2::Y))
		dirs.emplace_back(Vector2::Y);
	if (CheckAllCollider(Vector2::X))
		dirs.emplace_back(Vector2::X);
	if (CheckAllCollider(Vector2::NX))
		dirs.emplace_back(Vector2::NX);
	// No directions to move
	if (dirs.empty())
		mDir = Vector2::Zero;
	else
	{
		// Randomly choose a direction to move
		int index = Random::GetIntRange(0, dirs.size() - 1);
		mDir = dirs[index];
		// Set destination and start moving
		mDst = mGameObject->GetPosition() + mDir * 32;
		mIsMoving = true;
	}
}

void NavComponent::Chase()
// When player is close to the enemy, chase the player
{
	// Get current position and player's position
	Vector2 curPos = mGameObject->GetPosition();
	Vector2 playerPos = mPlayer->GetPosition();
	
	// Use for storing all the directions that can move
	std::vector<Vector2> dirs;
	// Add the directions that can move
	// Player is above the enemy
	if (playerPos.y < curPos.y && CheckAllCollider(Vector2::NY))
		dirs.emplace_back(Vector2::NY);
	// Player is below the enemy
	else if(playerPos.y > curPos.y && CheckAllCollider(Vector2::Y))
		dirs.emplace_back(Vector2::Y);
	// Player is on the left
	if (playerPos.x < curPos.x && CheckAllCollider(Vector2::NX))
		dirs.emplace_back(Vector2::NX);
	// Player is on the right
	else if (playerPos.x > curPos.x && CheckAllCollider(Vector2::X))
		dirs.emplace_back(Vector2::X);
	// No directions to move
	if (dirs.empty())
		mDir = Vector2::Zero;
	else
	{
		// Randomly choose a direction to move
		int index = Random::GetIntRange(0, dirs.size() - 1);
		mDir = dirs[index];
		// Set destination and start moving
		mDst = curPos + mDir * 32;
		mIsMoving = true;
	}
}

void NavComponent::ReachOneGrid()
// Have completed one grid's move
{
	mGameObject->SetPosition(mDst);
	mDir = Vector2::Zero;
	mPixelsCount = 0;
	mIsMoving = false;
}

int NavComponent::PlayerDistance()
// Get the distance between this and player's destination in grid
{
	Vector2 sub = mGameObject->GetPosition() - mPlayer->GetComponent<MoveComponent>()->GetDst();
	return static_cast<int>((Mathf::Abs(sub.x) + Mathf::Abs(sub.y)) / 32);
}

bool NavComponent::GetPlayerMoving()
{
	return mPlayer->GetComponent<MoveComponent>()->GetIsMoving();
}

bool NavComponent::CheckAllCollider(Vector2 dir)
// Check all the obstacles including wall, player, enemies
{
	// Check wall and enemies' current position
	bool check = WallCheck(dir) && ColliderCheck(dir);
	Vector2 tempDst = mGameObject->GetPosition() + dir * 32;
	if (tempDst == mPlayer->GetComponent<MoveComponent>()->GetDst())
		return false;

	// Check enemies' destination position
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