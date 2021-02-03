#pragma once
#include "Math.h"
#include "Game.h"
#include <vector>

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

	void UpdateGameObject();
	void LateUpdateGameObject();
	void UpdateComponents();
	void LateUpdateComponents();
	virtual void Update();
	virtual void LateUpdate();
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);


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
