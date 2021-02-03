#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(Game *game):
	mGame(game),
	mState(State::EActive),
	mPosition(Vector2::Zero),
	mScale(Vector2::One),
	mRotation(0.0f),
	mInputEnabled(true)
{
	mGame->CreateGameObject(this);
}

GameObject::~GameObject()
{
	mGame->RemoveGameObject(this);
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void GameObject::UpdateGameObject()
{
	if (mState == State::EActive)
	{
		UpdateComponents();
		Update();
	}
}

void GameObject::LateUpdateGameObject()
{
	if (mState == State::EActive)
	{
		LateUpdateComponents();
		LateUpdate();
	}
}

void GameObject::UpdateComponents()
{
	for (auto component : mComponents)
	{
		component->Update();
	}
}

void GameObject::LateUpdateComponents()
{
	for (auto component : mComponents)
	{
		component->LateUpdate();
	}
}

void GameObject::Update()
{

}

void GameObject::LateUpdate()
{

}

void GameObject::AddComponent(Component* component)
{
	int order = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for ( ;iter != mComponents.end(); ++iter)
	{
		if (order < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}
	mComponents.insert(iter, component);
}

void GameObject::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}
