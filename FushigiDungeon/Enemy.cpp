#include "Enemy.h"
#include "Game.h"
#include "AnimeSprite.h"
#include "NavComponent.h"
#include "AIComponent.h"
#include "AIState.h"
#include "Player.h"
#include <fstream>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json; 

Enemy::Enemy(Game* game, int number):
	GameObject(game),
	mNumber(number)
{
	// The enemy status for each type is in the data
	LoadData("Data/EnemyData.enmy", number);

	AnimeSprite* es = new AnimeSprite(this, 99);
	es->SetTexture(game->GetTexture(mName));

	NavComponent* nav = new NavComponent(this);
	nav->SetPlayer(game->GetPlayer());

	EnemyBattle* eb = new EnemyBattle(this, mStatus);

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

bool Enemy::LoadData(const std::string& fileName, int number)
// Get enmey status from the file
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		SDL_Log("File not found: Enemy %s", fileName.c_str());
		return false;
	}

	json j;
	file >> j;

	mName = j[mNumber]["name"];
	mStatus.level = j[mNumber]["level"];
	mStatus.maxHp = j[mNumber]["maxhp"];
	mStatus.curHp = mStatus.maxHp;
	mStatus.atk = j[mNumber]["atk"];
	mStatus.def = j[mNumber]["def"];
	mStatus.exp = j[mNumber]["exp"];

	return true;
}
