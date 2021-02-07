#pragma once
class Component
{
public:
	Component(class GameObject* gameObject);
	virtual ~Component();
	virtual void Update();
	virtual void LateUpdate();

	int GetUpdateOrder()const { return mUpdateOrder; }
	void SetUpdateOrder(int order) { mUpdateOrder = order; }
	int GetNumber() const { return mNumber; }
	class GameObject* GetGameObject() const { return mGameObject; }

protected:
	class GameObject* mGameObject;
	int mUpdateOrder;
	int mNumber;
};