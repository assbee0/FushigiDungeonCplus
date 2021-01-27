#pragma once
class Component
{
public:
	Component(class GameObject* gameObject);
	virtual ~Component();
	virtual void Update();

	int GetUpdateOrder()const { return mUpdateOrder; }
	void SetUpdateOrder(int order) { mUpdateOrder = order; }

protected:
	class GameObject* mGameObject;
	int mUpdateOrder;
};