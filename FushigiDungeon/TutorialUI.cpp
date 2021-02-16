#include "TutorialUI.h"
#include "Game.h"

TutorialUI::TutorialUI(Game* game):
	UIScreen(game)
{
	game->SetGameState(Game::GameState::GPaused);

	mTexBackground = game->GetTexture("Tutorial");
	mBackPos = Vector2(WINDOWS_WIDTH / 2, WINDOWS_HEIGHT / 2);
}

void TutorialUI::InputKeyPressed(int key)
{
	Mix_PlayChannel(-1, mGame->GetSound("Menu"), 0);
	Close();
}