#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject* gameObject):
	mGameObject(gameObject),
	mUpdateOrder(100)
{
	mGameObject->AddComponent(this);
}

Component::~Component()
{
	mGameObject->RemoveComponent(this);
}

void Component::Update()
{

}