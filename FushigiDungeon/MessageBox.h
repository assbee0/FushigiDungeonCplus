#pragma once
#include "UIScreen.h"

class MessageBox : public UIScreen
{
public:
	MessageBox(class Game* game);
	~MessageBox();

	void InputKeyPressed(int key) override;

protected:
	std::function<void()> virtual ConfirmOnClick();
	std::function<void()> CancelOnClick();
};

