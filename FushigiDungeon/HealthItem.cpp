#include "HealthItem.h"
#include "Game.h"
#include "SpriteComponent.h"

HealthItem::HealthItem(Game* game, int number) :
	GameObject(game),
	mNumber(number)
{
	SpriteComponent* sc = new SpriteComponent(this, 98);
	// The type of health items depends on number
	if (number == 1)
	{
		// Health 20% max hp
		mPercent = 20;
		sc->SetTexture(game->GetTexture("Yakusou"));
	}
	else
	{
		// Health 50% max hp
		mPercent = 50;
		sc->SetTexture(game->GetTexture("HpBox"));
	}
}

HealthItem::~HealthItem()
{
	GetGame()->SetHealthItem();
}
