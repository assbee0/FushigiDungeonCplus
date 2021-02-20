#include "MessageBox.h"
#include "Game.h"

MessageBox::MessageBox(Game* game):
	UIScreen(game)
{
	// Run into GPaused to process UI input
	game->SetGameState(Game::GameState::GPaused);
	Mix_PlayChannel(-1, mGame->GetSound("Menu"), 0);

	// Set background
	SDL_Renderer* renderer = game->GetRenderer();
	mTexBackground = game->GetTexture("MessageBack");
	mBackPos = Vector2(WINDOWS_WIDTH / 2, WINDOWS_HEIGHT / 2);
	// Set main text
	mTextCenter = false;
	mTextPos = Vector2(WINDOWS_WIDTH / 2, WINDOWS_HEIGHT * 2 / 5);
	SetText("Go to next floor ?", Vector3(0.286f, 0.141f, 0.055f), 28, renderer);

	// Set buttons
	mButtonOff = game->GetTexture("ButtonOffS");
	mButtonOn = game->GetTexture("ButtonOnS");
	// Two buttons are placed in horizontal
	Button* b1 = new Button(this);
	b1->SetPosition(Vector2(WINDOWS_WIDTH * 2 / 5, WINDOWS_HEIGHT * 3 / 5));
	b1->SetText("Yes", Vector3(0.898f, 0.835f, 0.737f), 18, renderer);
	b1->SetOnClick(ConfirmOnClick());

	Button* b2 = new Button(this);
	b2->SetPosition(Vector2(WINDOWS_WIDTH * 3 / 5, WINDOWS_HEIGHT * 3 / 5));
	b2->SetText("No", Vector3(0.898f, 0.835f, 0.737f), 18, renderer);
	b2->SetOnClick(CancelOnClick());
}

MessageBox::~MessageBox()
{
	//mGame->SetGameState(Game::GameState::GPlay);
}

void MessageBox::InputKeyPressed(int key)
{
	UIScreen::InputKeyPressed(key);

	switch (key)
	{
	case SDLK_ESCAPE:
		// Press esc to close the message box
		Mix_PlayChannel(-1, mGame->GetSound("Cancel"), 0);
		mGame->SetGameState(Game::GameState::GPlay);
		Close();
		break;
	case SDLK_LEFT:
	case SDLK_a:
	case SDLK_RIGHT:
	case SDLK_d:
		// Select two horizontal buttons
		// The first selected button is left button
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

std::function<void()> MessageBox::ConfirmOnClick()
{
	return [this]()
	{
		Close();
		Mix_PlayChannel(-1, mGame->GetSound("Stairs"), 0);
		mGame->SetGameState(Game::GameState::GPlay);
		// Generate and set new floor
		mGame->NewFloor();
	};
}

std::function<void()> MessageBox::CancelOnClick()
{
	return [this]()
	{
		Close();
		Mix_PlayChannel(-1, mGame->GetSound("Cancel"), 0);
		mGame->SetGameState(Game::GameState::GPlay);
	};
}
