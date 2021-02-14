#include "HealthItem.h"
#include "Game.h"
#include "SpriteComponent.h"

HealthItem::HealthItem(Game* game, int number) :
	GameObject(game),
	mNumber(number)
{
	SpriteComponent* sc = new SpriteComponent(this, 98);
	if (number == 1)
	{
		mPercent = 20;
		sc->SetTexture(game->GetTexture("Yakusou"));
	}
	else
	{
		mPercent = 50;
		sc->SetTexture(game->GetTexture("HpBox"));
	}
}

HealthItem::~HealthItem()
{
	GetGame()->SetHealthItem();
}

int HealthItem::PercentHealth(int maxHp)
{
	return maxHp * mPercent / 100;
}