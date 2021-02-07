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
	if (mComponent->GetEb()->IsDead())
	{
		mComponent->ChangeState("Death");
		return;
	}
	if (mComponent->GetStartMove())
	{
		if (mComponent->GetPlayerDis() <= 1)
		{
			mComponent->ChangeState("Attack");
		}
		else if (mComponent->GetPlayerDis() <= 6)
		{
			mComponent->ChangeState("Chase");
		}
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
	if (!mComponent->GetNav()->GetIsMoving())
	{
		mComponent->ChangeState("Idle");
	}
}

void AIChase::OnEnter()
{

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
	if (!mComponent->GetEb()->GetBattling())
	{
		mComponent->ChangeState("Idle");
	}
}

void AIAttack::OnEnter()
{
	mComponent->GetEb()->SetBattling();
	printf("caonima");
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