#include "BattleManager.h"
#include "GameObject.h"
#include "Enemy.h"
#include "MoveComponent.h"
#include "AIComponent.h"
#include "Player.h"

BattleManager::BattleManager(GameObject* gameObject):
	Component(gameObject),
	mTurnsCount(0),
	mIsInTurn(false)
{
	mNumber = 5;
}

void BattleManager::Update()
{
	if (mIsInTurn)
	{
		for (auto enemy : mGameObject->GetGame()->GetEnemies())
		{
			if (enemy->GetComponent<AIComponent>()->GetStartMove())
				return;
		}
		Player* player = mGameObject->GetGame()->GetPlayer();
		if (!player->GetComponent<MoveComponent>()->GetIsMoving())
		{
			player->SetInputEnabled(true);
			mIsInTurn = false;
		}
	}
}

void BattleManager::NewTurn()
{
	mTurnsCount++;
	for (auto enemy : mGameObject->GetGame()->GetEnemies())
	{
		enemy->GetComponent<AIComponent>()->SetStartMove(true);
	}
	mIsInTurn = true;
}