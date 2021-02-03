#pragma once
#include "Component.h"
#include "Math.h"
#include <vector>

class MoveComponent : public Component
{
public:
	MoveComponent(class GameObject* gameObject, bool isPlayer);
	void Update() override;
	
	void SetMap(int* map) { mMapArray = map; }
	void SetSpeed(float speed) { mSpeed = speed; }
	void SetDir(Vector2 dir);

private:

	void MoveOneGrid();
	bool WallCheck();
	bool ColliderCheck();

	int* mMapArray;
	std::vector<class Enemy*> mEnemies;

	Vector2 mDir;
	Vector2 mDst;
	bool mIsMoving;
	bool mIsPlayer;
	float mPixelsCount;
	float mSpeed;
};