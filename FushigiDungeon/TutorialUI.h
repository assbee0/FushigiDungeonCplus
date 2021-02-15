#pragma once
#include "UIScreen.h"

class TutorialUI : public UIScreen
{
public:
	TutorialUI(class Game* game);
	void InputKeyPressed(int key) override;
};