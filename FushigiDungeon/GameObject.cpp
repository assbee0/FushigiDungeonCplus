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
// Update per frame, cannot be override
{
	if (mState == State::EActive)
	{
		UpdateComponents();
		Update();
	}
}

void GameObject::LateUpdateGameObject()
// LateUpdate is called after Update, cannot be override
{
	if (mState == State::EActive)
	{
		LateUpdateComponents();
		LateUpdate();
	}
}

void GameObject::UpdateComponents()
// Update components attached to this game object per frame
{
	for (auto component : mComponents)
	{
		component->Update();
	}
}

void GameObject::LateUpdateComponents()
// LateUpdate is called after Update
{
	for (auto component : mComponents)
	{
		component->LateUpdate();
	}
}

void GameObject::Update()
// Can be override
{

}

void GameObject::LateUpdate()
// Can be override
{

}

void GameObject::AddComponent(Component* component)
{
	// Components have their update order
	int order = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	// New component has to be inserted in order
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
