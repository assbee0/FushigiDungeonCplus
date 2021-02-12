#pragma once
#include "GameObject.h"
#include "SDL.h"

class Player : public GameObject
{
public:
	Player(class Game* game);
	void ProcessInput(const Uint8* state);
	void InputKeyPressed(int key);
	void Update() override;


private:
	class MoveComponent* mc;
	class BattleComponent* bc;

};