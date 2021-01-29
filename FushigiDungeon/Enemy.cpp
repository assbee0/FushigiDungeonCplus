#include "Enemy.h"
#include "Game.h"
#include "SpriteComponent.h"

Enemy::Enemy(Game* game):
	GameObject(game),
	mHp(10)
{
	SpriteComponent* es = new SpriteComponent(this, 99);
	es->SetTexture(game->GetTexture("Enemy1"));
	
	game->CreateEnemy(this);
}

Enemy::~Enemy()
{
	GetGame()->RemoveGameObject(this);
}

void Enemy::BeAttacked(int damage)
{
	mHp -= damage;
	if (mHp < 0)
	{
		delete this;
		printf("wosile");
	}
}