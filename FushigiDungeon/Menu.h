#pragma once
#include "UIScreen.h"

class Menu : public UIScreen
{
public:
	Menu(class Game* game);
	~Menu();

	void InputKeyPressed(int key) override;

private:
	std::function<void()> ResumeOnClick();
	std::function<void()> HelpOnClick();
	std::function<void()> QuitOnClick();

};