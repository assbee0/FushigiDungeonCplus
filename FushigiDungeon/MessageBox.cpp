#include "MessageBox.h"
#include "Game.h"

MessageBox::MessageBox(Game* game):
	UIScreen(game)
{
	game->SetGameState(Game::GameState::GPaused);

	SDL_Renderer* renderer = game->GetRenderer();
	mTexBackground = game->GetTexture("MessageBack");
	mBackPos = Vector2(WINDOWS_WIDTH / 2, WINDOWS_HEIGHT / 2);

	mTextCenter = false;
	mTextPos = Vector2(WINDOWS_WIDTH / 2, WINDOWS_HEIGHT * 2 / 5);
	SetText("Go to next floor ?", Vector3(0.286f, 0.141f, 0.055f), 28, renderer);

	mButtonOff = game->GetTexture("ButtonOffS");
	mButtonOn = game->GetTexture("ButtonOnS");

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
	mGame->SetGameState(Game::GameState::GPlay);
}

void MessageBox::InputKeyPressed(int key)
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

std::function<void()> MessageBox::ConfirmOnClick()
{
	return [this]()
	{
		Close();
		mGame->NewFloor();
	};
}

std::function<void()> MessageBox::CancelOnClick()
{
	return [this]()
	{
		Close();
	};
}
