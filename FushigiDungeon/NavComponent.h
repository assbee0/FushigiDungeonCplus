#pragma once
#include "MoveComponent.h"
#include "Math.h"
#include <unordered_map>
#include <vector>

class NavComponent : public MoveComponent
{
public:
	NavComponent(class GameObject* gameObject);
	
	void Update() override;
	// When player is far from the enemy, wander
	void Wander();
	// When player is close to the enemy, chase the player
	void Chase();
	// Get the distance between this and player's destination in grid
	int PlayerDistance();

	void SetPlayer(class Player* player) { mPlayer = player; }
	bool GetPlayerMoving();

private:
	// Have completed one grid's move
	void ReachOneGrid() override;
	// Check all the obstacles including wall, player, enemies
	bool CheckAllCollider(Vector2 dir);

	class Player* mPlayer;
};
