#include "Camera.h"
#include "Game.h"
#include "CameraLock.h"

Camera::Camera(Game* game):
	GameObject(game)
{
	CameraLock* camLock = new CameraLock(this);
}

void Camera::LateUpdate()
{

}