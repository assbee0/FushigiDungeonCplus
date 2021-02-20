#pragma once
#include "UIScreen.h"

class GameOverUI : public UIScreen
{
public:
	GameOverUI(class Game* game, int level, int floor);
	~GameOverUI();

	// Input from keyboard pressed
	void InputKeyPressed(int key) override;

private:
	// GameOverUI has sub texts, so override
	void Draw(SDL_Renderer* renderer) override;
	// Set two sub texts
	void SetSubText(const std::string& text1, const std::string& text2, const Vector3& color, int size, SDL_Renderer* renderer);
	std::function<void()> QuitOnClick();
	std::function<void()> RestartOnClick();

	SDL_Texture* mFloorText;
	SDL_Texture* mLevelText;
};