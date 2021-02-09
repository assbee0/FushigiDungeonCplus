#pragma once
#include "MoveComponent.h"
#include "Math.h"
#include <unordered_map>
#include <vector>

class NavComponent : public MoveComponent
{
public:
	NavComponent(class GameObject* gameObject);
	void Wander();
	void Chase();
	int PlayerDistance();

	void SetPlayer(class Player* player) { mPlayer = player; }
	bool GetPlayerMoving();

private:
	void ReachOneGrid() override;
	bool CheckAllCollider(Vector2 dir);

	class Player* mPlayer;
};
