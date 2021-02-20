#pragma once
#include "GameObject.h"
#include "SDL.h"

class Player : public GameObject
{
public:
	Player(class Game* game);
	// Input from keyboard state
	void ProcessInput(const Uint8* state);
	// Input from keyboard pressed
	void InputKeyPressed(int key);


private:
	class MoveComponent* mc;
	class BattleComponent* bc;

};