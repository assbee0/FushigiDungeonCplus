#include "Enemy.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "NavComponent.h"
#include "AIComponent.h"
#include "AIState.h"
#include "Player.h"
#include "EnemyBattle.h"

Enemy::Enemy(Game* game):
	GameObject(game)
{
	SpriteComponent* es = new SpriteComponent(this, 99);
	es->SetTexture(game->GetTexture("Enemy1"));

	NavComponent* nav = new NavComponent(this);
	nav->SetPlayer(game->GetPlayer());

	EnemyBattle* eb = new EnemyBattle(this);

	AIComponent* ai = new AIComponent(this); 
	ai->RegisterState(new AIIdle(ai));
	ai->RegisterState(new AIWander(ai));
	ai->RegisterState(new AIChase(ai));
	ai->RegisterState(new AIAttack(ai));
	ai->RegisterState(new AIDeath(ai));
	ai->ChangeState("Idle");
	
	game->CreateEnemy(this);
}

Enemy::~Enemy()
{
	GetGame()->RemoveGameObject(this);
	GetGame()->RemoveEnemy(this);
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}
