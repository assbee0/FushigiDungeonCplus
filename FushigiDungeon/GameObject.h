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
	void UpdateComponents();
	virtual void Update();
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	class Game* GetGame() const { return mGame; }
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }
	Vector2 GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& p) { mPosition = p; }
	Vector2 GetScale() const { return mScale; }
	void SetScale(Vector2 s) { mScale = s; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float r) { mRotation = r; }


private:
	class Game* mGame;
	State mState;
	Vector2 mPosition;
	Vector2 mScale;
	float mRotation;

	std::vector<class Component*> mComponents;
};
