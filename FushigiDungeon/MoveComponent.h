#pragma once
#include "Component.h"
#include "Math.h"
#include <vector>

class MoveComponent : public Component
{
public:
	MoveComponent(class GameObject* gameObject, bool isPlayer);
	void Update() override;
	
	bool GetIsMoving() const { return mIsMoving; }
	void SetMap(class Map* map) { mMap = map; }
	void SetSpeed(float speed) { mSpeed = speed; }
	void SetDir(Vector2 dir);

protected:

	void MoveOneGrid();
	bool WallCheck();
	bool ColliderCheck();
	virtual void ReachOneGrid();

	class Map* mMap;
	std::vector<class Enemy*> mEnemies;

	Vector2 mDir;
	Vector2 mDst;
	bool mIsMoving;
	bool mIsPlayer;
	float mPixelsCount;
	float mSpeed;
};