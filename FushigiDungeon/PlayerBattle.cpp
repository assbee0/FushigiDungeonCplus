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
	Mix_PlayChannel(-1, mGameObject->GetGame()->GetSound("Attack1"), 0);
	// If the enemy is defeated, get exp from enemy
	if (mTarget->IsDead())
	{
		// Player's exp variable is exp needed to next level
		// While enemy's exp variable is exp can get by player when it is defeated
		mStatus.exp -= mTarget->GetExp();
		// Check and process level up
		LevelUp();
		UpdateHUD();
	}
}

void PlayerBattle::BeAttacked(int damage)
{
	BattleComponent::BeAttacked(damage);

	UpdateHUD();

	// If player is dead, game over
	if (IsDead())
	{
		Mix_PlayMusic(mGameObject->GetGame()->GetMusic("Defeat"), 1);
		new GameOverUI(mGameObject->GetGame(), mStatus.level, mGameObject->GetGame()->GetDungeon()->GetFloor());
	}
}

void PlayerBattle::AttackOver()
{
	BattleComponent::AttackOver();
	Mix_PlayChannel(-1, mGameObject->GetGame()->GetSound("Attack3"), 0);
	// When player's attack is over, start a new turn
	mGameObject->GetGame()->GetDungeon()
		->GetComponent<BattleManager>()->NewTurn();
}

void PlayerBattle::RecoverHp(int curePercent)
// Pick up health item and use it to recover current hp
{
	// Herb
	if (curePercent == 20)
		Mix_PlayChannel(-1, mGameObject->GetGame()->GetSound("Cure1"), 0);
	// Aid box
	else
		Mix_PlayChannel(-1, mGameObject->GetGame()->GetSound("Cure2"), 0);
	int cure = mStatus.maxHp * curePercent / 100;
	mStatus.curHp += cure;
	// Cure hp can't beyond max hp
	if (mStatus.curHp > mStatus.maxHp)
	{
		mStatus.curHp = mStatus.maxHp;
	}
	UpdateHUD();
}

void PlayerBattle::LevelUp()
// Check and process level up
{
	// Exp needed to next level is smaller than zero, level up 
	if (mStatus.exp <= 0)
	{
		// Temporarly store the overflow exp
		int expOverflow = -mStatus.exp;
		mStatus.level++;
		// Some status increase more when level is high
		mStatus.maxHp += 2 + mStatus.level / 5;
		mStatus.curHp += 2 + mStatus.level / 5;
		mStatus.atk += 1 + mStatus.level / 5;
		mStatus.def += 1 + mStatus.level / 5;
		// Exp needed to next level is depending on current level and exp needed last level
		mStatus.exp = mPreNeededExp + 3 * mStatus.level;
		mPreNeededExp = mStatus.exp;
		// Process overflow exp
		mStatus.exp -= expOverflow;
		Mix_PlayChannel(-1, mGameObject->GetGame()->GetSound("LevelUp"), 0);
	}
}

void PlayerBattle::UpdateHUD()
// When player status changed, update the values in HUD
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