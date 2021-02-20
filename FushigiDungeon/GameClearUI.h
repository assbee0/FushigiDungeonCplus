#pragma once
#include "UIScreen.h"

class GameClearUI : public UIScreen
{
public:
	GameClearUI(class Game* game);
	// Input from keyboard pressed
	void InputKeyPressed(int key) override;

private:
	std::function<void()> QuitOnClick();
	std::function<void()> RestartOnClick();
};