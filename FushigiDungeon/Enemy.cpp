#include "Enemy.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"

Enemy::Enemy(Game* game):
	GameObject(game),
	mHp(10)
{
	SpriteComponent* es = new SpriteComponent(this, 99);
	es->SetTexture(game->GetTexture("Enemy1"));
	
	mc = new MoveComponent(this, false);
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

void Enemy::BeAttacked(int damage)
{
	mHp -= damage;
	if (mHp < 0)
	{
		SetState(State::EDead);
		printf("wosile");
	}
}