#pragma once
#include "Component.h"
#include "Math.h"

class MoveComponent : public Component
{
public:
	MoveComponent(class GameObject* gameObject);
	void Update() override;
	enum class Direction
	{
		Up,
		Down,
		Left,
		Right
	};

	
	void SetMap(int* map) { mMapArray = map; }
	void SetSpeed(float speed) { mSpeed = speed; }
	void SetDir(Direction dir);

private:

	void MoveOneGrid();
	bool WallCheck();

	int* mMapArray;

	Vector2 mDir;
	Vector2 mDst;
	bool mIsMoving;
	float mPixelsCount;
	float mSpeed;
};