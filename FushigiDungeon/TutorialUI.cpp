#include "TutorialUI.h"
#include "Game.h"

TutorialUI::TutorialUI(Game* game):
	UIScreen(game)
{
	// Run into GPaused to process UI input
	game->SetGameState(Game::GameState::GPaused);

	// This UI has only background
	mTexBackground = game->GetTexture("Tutorial");
	mBackPos = Vector2(WINDOWS_WIDTH / 2, WINDOWS_HEIGHT / 2);
}

void TutorialUI::InputKeyPressed(int key)
// Input from keyboard pressed
{
	// Press any key to close this UI
	Mix_PlayChannel(-1, mGame->GetSound("Menu"), 0);
	Close();
}