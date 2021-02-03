#include "BattleManager.h"
#include "GameObject.h"
#include "Enemy.h"
#include "MoveComponent.h"

BattleManager::BattleManager(GameObject* gameObject):
	Component(gameObject),
	mTurnsCount(0)
{
	mNumber = 5;
}

void BattleManager::Update()
{
}

void BattleManager::NewTurn()
{
	mTurnsCount++;
	for (auto enemy : mGameObject->GetGame()->GetEnemies())
	{
		enemy->GetComponent<MoveComponent>()->SetDir(Vector2::X);
	}
}