#pragma once
#include "Component.h"
#include <unordered_map>
#include <string>

class AIComponent : public Component
{
public:
	AIComponent(class GameObject* gameObject);
	void Update() override;
	void ChangeState(const std::string& name);
	void RegisterState(class AIState* state);
	bool GetIsIdle();

	int GetPlayerDis() const { return mPlayerDistance; }
	void SetStartMove(bool start);
	bool GetStartMove() const { return mStartMove; }
	bool GetEndMove() const { return mEndMove; }
	class NavComponent* GetNav() const { return mNav; }
	class EnemyBattle* GetEb() const { return mEb; }

private:
	std::unordered_map<std::string, class AIState*> mStateMap;
	class AIState* mCurState;
	bool mStartMove;
	bool mEndMove;
	class NavComponent* mNav;
	class EnemyBattle* mEb;
	int mPlayerDistance;
};