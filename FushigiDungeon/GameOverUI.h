#pragma once
#include "UIScreen.h"

class GameOverUI : public UIScreen
{
public:
	GameOverUI(class Game* game, int level, int floor);
	~GameOverUI();

	void InputKeyPressed(int key) override;

private:
	void Draw(SDL_Renderer* renderer) override;
	void SetSubText(const std::string& text1, const std::string& text2, const Vector3& color, int size, SDL_Renderer* renderer);
	std::function<void()> QuitOnClick();
	std::function<void()> RestartOnClick();

	SDL_Texture* mFloorText;
	SDL_Texture* mLevelText;
};