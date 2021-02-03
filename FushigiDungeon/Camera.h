#pragma once
#include "GameObject.h"
class Camera : public GameObject
{
public:
	Camera(class Game* game);
	void LateUpdate() override;
};