#pragma once
#include "Math.h"
#include "Game.h"

class GameObject
{
public:
	enum class State
	{
		EActive,
		EPaused,
		EDead
	};
	GameObject(class Game* game);
	virtual ~GameObject();

	// Update per frame, cannot be override
	void UpdateGameObject();
	// LateUpdate is called after Update, cannot be override
	void LateUpdateGameObject();
	// Update components attached to this game object per frame
	void UpdateComponents();
	// LateUpdate is called after Update
	void LateUpdateComponents();
	// Can be override
	virtual void Update();
	// Can be override
	virtual void LateUpdate();
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	// Get the component from the object, and transform its type to subclass T
	template<typename T> T* GetComponent()
	{
		for (auto com : mComponents)
		{
			T* component = dynamic_cast<T*>(com);
			if (component != nullptr)
			{
				return component;
			}
		}
		return nullptr;
	}


	class Game* GetGame() const { return mGame; }
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }
	Vector2 GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& p) { mPosition = p; }
	Vector2 GetScale() const { return mScale; }
	void SetScale(Vector2 s) { mScale = s; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float r) { mRotation = r; }
	void SetInputEnabled(bool e) { mInputEnabled = e; }

protected:
	bool mInputEnabled;
	std::vector<class Component*> mComponents;

private:
	class Game* mGame;
	State mState;
	Vector2 mPosition;
	Vector2 mScale;
	float mRotation;


};
