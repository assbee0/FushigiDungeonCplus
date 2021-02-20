#include "Menu.h"
#include "Game.h"
#include "TutorialUI.h"

Menu::Menu(Game* game):
	UIScreen(game)
{
	// Run into GPaused to process UI input
	mGame->SetGameState(Game::GameState::GPaused);
	Mix_PlayChannel(-1, mGame->GetSound("Menu"), 0);
	
	// Set background
	SDL_Renderer* renderer = game->GetRenderer();
	mTexBackground = game->GetTexture("MenuBack");
	mBackPos = Vector2(WINDOWS_WIDTH / 2, WINDOWS_HEIGHT / 2);
	// Set main text
	mTextCenter = false;
	mTextPos = Vector2(WINDOWS_WIDTH / 2, WINDOWS_HEIGHT / 4);
	SetText("Menu", Vector3(0.286f, 0.141f, 0.055f), 24, renderer);

	// Set buttons
	mButtonOff = game->GetTexture("ButtonOff");
	mButtonOn = game->GetTexture("ButtonOn");
	// Three buttons are placed in vertical
	Button* b1 = new Button(this);
	b1->SetPosition(Vector2(WINDOWS_WIDTH / 2, 180));
	b1->SetText("Resume", Vector3(0.898f, 0.835f, 0.737f), 18, renderer);
	b1->SetOnClick(ResumeOnClick());

	Button* b2 = new Button(this);
	b2->SetPosition(Vector2(WINDOWS_WIDTH / 2, 250));
	b2->SetText("Help", Vector3(0.898f, 0.835f, 0.737f), 18, renderer);
	b2->SetOnClick(HelpOnClick());

	Button* b3 = new Button(this);
	b3->SetPosition(Vector2(WINDOWS_WIDTH / 2, 320));
	b3->SetText("Quit", Vector3(0.898f, 0.835f, 0.737f), 18, renderer);
	b3->SetOnClick(QuitOnClick());
}

Menu::~Menu()
{
	mGame->SetGameState(Game::GameState::GPlay);
}

void Menu::InputKeyPressed(int key)
// Input from keyboard pressed
{
	UIScreen::InputKeyPressed(key);

	switch (key)
	{
	case SDLK_ESCAPE:
		// Press esc to close the menu
		Mix_PlayChannel(-1, mGame->GetSound("Cancel"), 0);
		Close();
		break;

	case SDLK_DOWN:
	case SDLK_s:
		// Select three vertical buttons
		// The first selected button is top button
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
			mCurButton = mButtons[2];
			mCurButton->SetIsSelected(true);
		}
		else if (mCurButton == mButtons[2])
		{
			mCurButton->SetIsSelected(false);
			mCurButton = mButtons[0];
			mCurButton->SetIsSelected(true);
		}
		break;
	case SDLK_UP:
	case SDLK_w:
		if (mCurButton == nullptr)
		{
			ResetButtonState();
			mCurButton = mButtons[0];
			mCurButton->SetIsSelected(true);
		}
		else if (mCurButton == mButtons[0])
		{
			mCurButton->SetIsSelected(false);
			mCurButton = mButtons[2];
			mCurButton->SetIsSelected(true);
		}
		else if (mCurButton == mButtons[1])
		{
			mCurButton->SetIsSelected(false);
			mCurButton = mButtons[0];
			mCurButton->SetIsSelected(true);
		}
		else if (mCurButton == mButtons[2])
		{
			mCurButton->SetIsSelected(false);
			mCurButton = mButtons[1];
			mCurButton->SetIsSelected(true);
		}
		break;
	default:
		break;
	}
}

std::function<void()> Menu::ResumeOnClick()
{
	return [this]()
	{
		Mix_PlayChannel(-1, mGame->GetSound("Menu"), 0);
		Close();
	};
}

std::function<void()> Menu::HelpOnClick()
{
	return [this]()
	{
		Mix_PlayChannel(-1, mGame->GetSound("Menu"), 0);
		new TutorialUI(mGame);
	};
}

std::function<void()> Menu::QuitOnClick()
{
	return [this]()
	{
		mGame->SetGameState(Game::GameState::GQuit);
	};
}
