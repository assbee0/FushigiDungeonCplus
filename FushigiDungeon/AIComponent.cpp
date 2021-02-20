#include "AIComponent.h"
#include "GameObject.h"
#include "AIState.h"
#include "NavComponent.h"
#include "EnemyBattle.h"

AIComponent::AIComponent(GameObject* gameObject):
	Component(gameObject),
	mCurState(nullptr),
	mStartMove(false),
	mEndMove(true),
	mNav(nullptr),
	mPlayerDistance(-1)
{
	mNav = gameObject->GetComponent<NavComponent>();
	mEb = gameObject->GetComponent<EnemyBattle>();
}

void AIComponent::Update()
{
	if (mCurState)
	{
		mCurState->Update();
	}
}

void AIComponent::ChangeState(const std::string& name)
{
	// Exit from the current state
	if (mCurState)
	{
		mCurState->OnExit();
	}
	// Enter the new state
	auto iter = mStateMap.find(name);
	if (iter != mStateMap.end())
	{
		mCurState = iter->second;
		mCurState->OnEnter();
	}
}

void AIComponent::RegisterState(AIState* state)
{
	mStateMap.emplace(state->GetName(), state);
}

bool AIComponent::GetIsIdle()
{
	if (mCurState->GetName() == "Idle")
		return true;
	else
		return false;
}

void AIComponent::SetStartMove(bool start)
{
	// announce this ai to start move
	mStartMove = start; 
	mPlayerDistance = mNav->PlayerDistance(); 
}