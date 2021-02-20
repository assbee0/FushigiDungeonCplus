#include "CameraLock.h"
#include "GameObject.h"
#include "Player.h"

CameraLock::CameraLock(GameObject* gameObject) :
	Component(gameObject),
	mPlayer(nullptr),
	mMapW(0),
	mMapH(0),
	mCenter(Vector2::Zero),
	mBuffer(Vector2::Zero)
{

}

void CameraLock::LateUpdate()
// After all the game objects have updated, camera starts its update
{
	// In the camera's coordinate system, player is always in the center
	mCenter = mPlayer->GetPosition();
	// Dual with situations when player is close to the edges of the map
	mBuffer.x = (mCenter.x - WINDOWS_WIDTH / 2) >= 0? (mCenter.x - WINDOWS_WIDTH / 2) : 0;
	mBuffer.y = (mCenter.y - 256) >= 0? (mCenter.y - 256) : 0;
	mBuffer.x = (mMapW - mBuffer.x) >= WINDOWS_WIDTH ? mBuffer.x : mMapW - WINDOWS_WIDTH;
	mBuffer.y = (mMapH - mBuffer.y) >= WINDOWS_HEIGHT ? mBuffer.y : mMapH - WINDOWS_HEIGHT;
}

Vector2 CameraLock::WorldToCamera(Vector2 worldPos)
{
	return worldPos - mBuffer;
}

Vector2 CameraLock::CameraToWorld(Vector2 camPos)
{
	return camPos + mBuffer;
}