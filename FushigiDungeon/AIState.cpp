#include "AIState.h"
#include "AIComponent.h"
#include "NavComponent.h"
#include "EnemyBattle.h"
#include "GameObject.h"

AIState::AIState(AIComponent* component) :
	mComponent(component)
{

}

void AIState::Update()
{

}

void AIState::OnEnter()
{

}

void AIState::OnExit()
{

}

AIIdle::AIIdle(AIComponent* component) :
	AIState(component)
{

}

void AIIdle::Update()
{
	// The enemy is dead, enter state Death
	if (mComponent->GetEb()->IsDead())
	{
		mComponent->ChangeState("Death");
		return;
	}
	// If the ai is asked to start move
	if (mComponent->GetStartMove())
	{
		// Beside the player, enter state Attack
		if (mComponent->GetPlayerDis() <= 1)
		{
			mComponent->ChangeState("Attack");
		}
		// The player is in the alert area of the enemy, enter state Chase
		else if (mComponent->GetPlayerDis() <= 6)
		{
			mComponent->ChangeState("Chase");
		}
		// The player is far from the enemy, enter state Wander
		else
		{
			mComponent->ChangeState("Wander");
		}
	}
}

void AIIdle::OnEnter()
{

}

void AIIdle::OnExit()
{

}

AIWander::AIWander(AIComponent* component) :
	AIState(component)
{

}

void AIWander::Update()
{
	// When moving a grid is over, return state Idle
	if (!mComponent->GetNav()->GetIsMoving())
	{
		mComponent->ChangeState("Idle");
	}
}

void AIWander::OnEnter()
{
	mComponent->GetNav()->Wander();
}

void AIWander::OnExit()
{
	mComponent->SetStartMove(false);
}

AIChase::AIChase(AIComponent* component) :
	AIState(component)
{

}

void AIChase::Update()
{
	// When moving a grid is over, return state Idle
	if (!mComponent->GetNav()->GetIsMoving())
	{
		mComponent->ChangeState("Idle");
	}
}

void AIChase::OnEnter()
{
	mComponent->GetNav()->Chase();
}

void AIChase::OnExit()
{
	mComponent->SetStartMove(false);
}

AIAttack::AIAttack(AIComponent* component) :
	AIState(component)
{

}

void AIAttack::Update()
{
	// When attacking is over, return state Idle
	if (!mComponent->GetEb()->GetBattling())
	{
		mComponent->ChangeState("Idle");
	}
}

void AIAttack::OnEnter()
{
	// inform the enemy battle object to start battle
	mComponent->GetEb()->SetBattling();
}

void AIAttack::OnExit()
{
	mComponent->SetStartMove(false);
}

AIDeath::AIDeath(AIComponent* component) :
	AIState(component)
{

}

void AIDeath::Update()
{

}

void AIDeath::OnEnter()
{
	mComponent->GetGameObject()->SetState(GameObject::State::EDead);
}

void AIDeath::OnExit()
{

}