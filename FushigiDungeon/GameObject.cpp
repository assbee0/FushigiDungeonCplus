#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(Game *game):
	mGame(game),
	mState(State::EActive),
	mPosition(Vector2::Zero),
	mScale(Vector2::One),
	mRotation(0.0f)
{
	mGame->CreateGameObject(this);
}

GameObject::~GameObject()
{
	mGame->RemoveGameObject(this);
	mComponents.clear();
	mComponents.shrink_to_fit();
}

void GameObject::UpdateGameObject()
{
	if (mState == State::EActive)
	{
		UpdateComponents();
		Update();
	}
}

void GameObject::UpdateComponents()
{
	for (auto component : mComponents)
	{
		component->Update();
	}
}

void GameObject::Update()
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