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
{
	mCenter = mPlayer->GetPosition();
	mBuffer.x = (mCenter.x - WINDOWS_WIDTH / 2) >= 0? (mCenter.x - WINDOWS_WIDTH / 2) : 0;
	mBuffer.y = (mCenter.y - 256) >= 0? (mCenter.y - 256) : 0;
	mBuffer.x = (mMapW - mBuffer.x) >= 640 ? mBuffer.x : mMapW - 640;
	mBuffer.y = (mMapH - mBuffer.y) >= 480 ? mBuffer.y : mMapH - 480;
}

Vector2 CameraLock::WorldToCamera(Vector2 worldPos)
{
	return worldPos - mBuffer;
}

Vector2 CameraLock::CameraToWorld(Vector2 camPos)
{
	return camPos + mBuffer;
}