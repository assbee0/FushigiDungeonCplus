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

}

void BattleManager::Update()
{
	// If this turn is not over
	if (mIsInTurn)
	{
		// Check if all the enemies has completed their moves
		for (auto enemy : mGameObject->GetGame()->GetEnemies())
		{
			if (enemy->GetComponent<AIComponent>()->GetStartMove())
				return;
		}
		// Check if player has completed his move
		Player* player = mGameObject->GetGame()->GetPlayer();
		if (!player->GetComponent<MoveComponent>()->GetIsMoving())
		{
			// Enable the input
			player->SetInputEnabled(true);
			// This turn is over
			mIsInTurn = false;
		}
	}
}

void BattleManager::NewTurn()
// When player takes action, this method is called to start a new turn
{
	mTurnsCount++;
	// Inform all the enemies to start moving
	for (auto enemy : mGameObject->GetGame()->GetEnemies())
	{
		enemy->GetComponent<AIComponent>()->SetStartMove(true);
	}
	// This turn started
	mIsInTurn = true;
}