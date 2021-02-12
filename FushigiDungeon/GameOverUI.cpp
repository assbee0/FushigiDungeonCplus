#include "GameOverUI.h"
#include "Game.h"
#include "Font.h"
#include <sstream>

GameOverUI::GameOverUI(Game* game, int level, int floor) :
	UIScreen(game),
	mFloorText(nullptr)
{
	game->SetGameState(Game::GameState::GPaused);

	SDL_Renderer* renderer = game->GetRenderer();
	mTexBackground = game->GetTexture("GameOver");
	mBackPos = Vector2(WINDOWS_WIDTH / 2, WINDOWS_HEIGHT / 2);

	mTextCenter = false;
	mTextPos = Vector2(WINDOWS_WIDTH / 2, WINDOWS_HEIGHT * 9 / 20);
	SetText("Result", Vector3(0.286f, 0.141f, 0.055f), 28, renderer);

	std::stringstream ss1, ss2;
	ss1 << "Floor: " << floor;
	ss2 << "Level: " << level;
	SetSubText(ss1.str(), ss2.str(), Vector3(0.286f, 0.141f, 0.055f), 24, renderer);
	
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

GameOverUI::~GameOverUI()
{
	if (mFloorText)
	{
		SDL_DestroyTexture(mFloorText);
	}
	if (mLevelText)
	{
		SDL_DestroyTexture(mLevelText);
	}
}

void GameOverUI::InputKeyPressed(int key)
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

void GameOverUI::Draw(SDL_Renderer* renderer)
{
	UIScreen::Draw(renderer);
	if (mFloorText)
	{
		SDL_Rect dstRect = TextureRect(mFloorText, Vector2(WINDOWS_WIDTH / 2, WINDOWS_HEIGHT * 11 / 20));
		SDL_RenderCopy(renderer, mFloorText, nullptr, &dstRect);
	}
	if (mLevelText)
	{
		SDL_Rect dstRect = TextureRect(mLevelText, Vector2(WINDOWS_WIDTH / 2, WINDOWS_HEIGHT * 13 / 20));
		SDL_RenderCopy(renderer, mLevelText, nullptr, &dstRect);
	}
}

void GameOverUI::SetSubText(const std::string& text1, const std::string& text2, const Vector3& color, int size, SDL_Renderer* renderer)
{
	if (mFloorText)
	{
		SDL_DestroyTexture(mFloorText);
		mFloorText = nullptr;
	}
	SDL_Surface* surf = mFont->CreateText(text1, color, size);
	if (surf)
	{
		mFloorText = SDL_CreateTextureFromSurface(renderer, surf);
		SDL_FreeSurface(surf);
	}

	if (mLevelText)
	{
		SDL_DestroyTexture(mLevelText);
		mLevelText = nullptr;
	}
	surf = mFont->CreateText(text2, color, size);
	if (surf)
	{
		mLevelText = SDL_CreateTextureFromSurface(renderer, surf);
		SDL_FreeSurface(surf);
	}
}

std::function<void()> GameOverUI::QuitOnClick()
{
	return [this]()
	{
		mGame->SetGameState(Game::GameState::GQuit);
	};
}

std::function<void()> GameOverUI::RestartOnClick()
{
	return [this]()
	{
		mGame->Restart();
	};
}