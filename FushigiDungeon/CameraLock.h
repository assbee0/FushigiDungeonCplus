#pragma once
#include "Component.h"
#include "Math.h"

class CameraLock : public Component
{
public:
	CameraLock(class GameObject* gameObject);
	void LateUpdate() override;
	Vector2 WorldToCamera(Vector2 worldPos);
	Vector2 CameraToWorld(Vector2 camPos);

	void SetPlayer(class Player* player) { mPlayer = player; }
	void SetMapW(int w) { mMapW = w; }
	void SetMapH(int h) { mMapH = h; }


private:

	class Player* mPlayer;
    int mMapW;
    int mMapH;
	Vector2 mCenter;
	Vector2 mBuffer;
};