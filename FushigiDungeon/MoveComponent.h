#pragma once
#include "Component.h"
#include "Math.h"
#include <vector>

class MoveComponent : public Component
{
public:
	MoveComponent(class GameObject* gameObject);
	void Update() override;
	
	// Set the moving direction, if no obstacle, start moving
	void SetDir(Vector2 dir);

	Vector2 GetDst()const { return mDst; }
	void SetDst(Vector2 dst) { mDst = dst; }
	bool GetIsMoving() const { return mIsMoving; }
	void SetMap(class Map* map) { mMap = map; }
	float GetSpeed() const { return mSpeed; }
	void SetSpeed(float speed) { mSpeed = speed; }

protected:
	// Move from a grid to an adjacent grid
	void MoveOneGrid();
	// Check if there is a wall at the direction dir
	bool WallCheck(Vector2 dir);
	// Check if there is an enemy at the direction dir
	bool ColliderCheck(Vector2 dir);
	// Have completed one grid's move, interact with the objects on the destination
	virtual void ReachOneGrid();

	class Map* mMap;
	std::vector<class Enemy*> mEnemies;

	// Moving direction
	Vector2 mDir;
	// Moving destination
	Vector2 mDst;
	bool mIsMoving;
	// Pixels moved while moving
	float mPixelsCount;
	float mSpeed;
};