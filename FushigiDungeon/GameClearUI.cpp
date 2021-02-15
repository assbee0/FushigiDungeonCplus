#include "GameClearUI.h"
#include "Game.h"

GameClearUI::GameClearUI(Game* game):
	UIScreen(game)
{
	game->SetGameState(Game::GameState::GPaused);

	SDL_Renderer* renderer = game->GetRenderer();
	mTexBackground = game->GetTexture("GameClear");
	mBackPos = Vector2(WINDOWS_WIDTH / 2, WINDOWS_HEIGHT / 2);

	mButtonOff = game->GetTexture("ButtonOff");
	mButtonOn = game->GetTexture("ButtonOn");

	Button* b1 = new Button(this);
	b1->SetPosition(Vector2(WINDOWS_WIDTH / 3, 420));
	b1->SetText("Restart", Vector3(0.898f, 0.835f, 0.737f), 18, renderer);
	b1->SetOnClick(RestartOnClick());

	Button* b2 = new Button(this);
	b2->SetPosition(Vector2(WINDOWS_WIDTH * 2 / 3, 420));
	b2->SetText("Quit", Vector3(0.898f, 0.835f, 0.737f), 18, renderer);
	b2->SetOnClick(QuitOnClick());
}

void GameClearUI::InputKeyPressed(int key)
{
	UIScreen::InputKeyPressed(key);
	switch (key)
	{
	case SDLK_LEFT:
	case SDLK_a:
	case SDLK_RIGHT:
	case SDLK_d:
		if (mCurButton == nullptr)
		{
			ResetButtonState();
			mCurButton = mButtons[0];
			mCurButton->SetIsSelected(true);
		}
		else if (mCurButton == mButtons[0])
		{
			mCurButton->SetIsSelected(false);
			mCurButton = mButtons[1];
			mCurButton->SetIsSelected(true);
		}
		else if (mCurButton == mButtons[1])
		{
			mCurButton->SetIsSelected(false);
			mCurButton = mButtons[0];
			mCurButton->SetIsSelected(true);
		}
		break;
	default:
		break;
	}
}

std::function<void()> GameClearUI::QuitOnClick()
{
	return [this]()
	{
		mGame->SetGameState(Game::GameState::GQuit);
	};
}

std::function<void()> GameClearUI::RestartOnClick()
{
	return [this]()
	{
		mGame->Restart();
	};
}