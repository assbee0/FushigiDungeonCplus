#pragma once
#include "MoveComponent.h"

class NavComponent : public MoveComponent
{
public:
	NavComponent(class GameObject* gameObject);
	void Wander();
	int PlayerDistance();

	void SetPlayer(class Player* player) { mPlayer = player; }

private:
	void ReachOneGrid() override;

	class Player* mPlayer;
};