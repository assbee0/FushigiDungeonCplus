#pragma once
#include "GameObject.h"
#include "SDL.h"

class Player : public GameObject
{
public:
	Player(class Game* game);
	void ProcessInput(const Uint8* state);
	void Update() override;

	void SetMap(int* map);

private:
	const int PLAYER_SPEED = 200;
	bool mIsWalking;
	Vector2 mVec;
	//ÿ����һ����Ż���µ�λ�ñ���
	Vector2 mPos;
	Vector2 mDst;
	float mPixelsCount;

	class MoveComponent* mc;
};