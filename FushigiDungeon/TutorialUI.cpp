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
	Close();
}