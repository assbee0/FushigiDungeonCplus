#include "PlayerBattle.h"
#include "GameObject.h"
#include "HUD.h"
#include "GameOverUI.h"
#include "Dungeon.h"
#include "BattleManager.h"
#include "Random.h"

PlayerBattle::PlayerBattle(GameObject* gameObject):
	BattleComponent(gameObject),
	mPreNeededExp(mStatus.exp)
{
	
}

void PlayerBattle::AttackTarget()
{
	BattleComponent::AttackTarget();
	if (mTarget->IsDead())
	{
		mStatus.exp -= mTarget->GetExp();
		LevelUp();
		UpdateHUD();
	}
}

void PlayerBattle::BeAttacked(int damage)
{
	BattleComponent::BeAttacked(damage);

	UpdateHUD();

	printf("HP:%d / %d\n", mStatus.curHp, mStatus.maxHp);
	if (IsDead())
	{
		printf("ÄãÀ­Ï¡ÁË\n");
		new GameOverUI(mGameObject->GetGame(), mStatus.level, mGameObject->GetGame()->GetDungeon()->GetFloor());
		//mGameObject->GetGame()->SetGameState(Game::GameState::GQuit);
	}
}

void PlayerBattle::AttackOver()
{
	BattleComponent::AttackOver();
	mGameObject->GetGame()->GetDungeon()
		->GetComponent<BattleManager>()->NewTurn();
}

void PlayerBattle::RecoverHp(int curePercent)
{
	int cure = mStatus.maxHp * curePercent / 100;
	mStatus.curHp += cure;
	if (mStatus.curHp > mStatus.maxHp)
	{
		mStatus.curHp = mStatus.maxHp;
	}
	UpdateHUD();
}

void PlayerBattle::LevelUp()
{
	if (mStatus.exp <= 0)
	{
		int expOverflow = -mStatus.exp;
		mStatus.level++;
		mStatus.maxHp += 2 + mStatus.level / 5;
		mStatus.curHp += 2 + mStatus.level / 5;
		mStatus.atk += 1 + mStatus.level / 5;
		mStatus.def += 1 + mStatus.level / 5;
		mStatus.exp = mPreNeededExp + 3 * mStatus.level;
		mPreNeededExp = mStatus.exp;
		mStatus.exp -= expOverflow;
	}
}

void PlayerBattle::UpdateHUD()
{
	mGameObject->GetGame()->GetHUD()->SetStatus
	(
		mStatus.level,
		mStatus.curHp,
		mStatus.maxHp,
		mStatus.atk,
		mStatus.def,
		mStatus.exp
	);
}