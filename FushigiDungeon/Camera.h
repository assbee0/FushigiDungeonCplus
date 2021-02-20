#pragma once
#include "GameObject.h"
class Camera : public GameObject
{
public:
	Camera(class Game* game);
	// After all the game objects have updated, camera starts its update
	void LateUpdate() override;
};