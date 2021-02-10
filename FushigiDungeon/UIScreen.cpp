#include "UIScreen.h"
#include "Game.h"
#include "Font.h"

UIScreen::UIScreen(Game* game):
	mGame(game),
	mState(UIState::UActive),
	mBackPos(Vector2::Zero),
	mTexBackground(nullptr),
	mTextPos(Vector2::Zero),
	mText(nullptr),
	mTextCenter(true)
{
	mGame->PushUI(this);
	mFont = mGame->GetFont();
}

UIScreen::~UIScreen()
{

}

void UIScreen::ProcessInput(const uint8_t* state)
{

}

void UIScreen::Update()
{

}

void UIScreen::Draw(SDL_Renderer* renderer)
{

}

void UIScreen::SetText(const std::string& text, const Vector3& color, int size, SDL_Renderer* renderer)
{
	if (mText)
	{
		SDL_DestroyTexture(mText);
		mText = nullptr;
	}
	SDL_Surface* surf = mFont->CreateText(text, color, size);
	if (surf)
	{
		mText = SDL_CreateTextureFromSurface(renderer, surf);
		SDL_FreeSurface(surf);
	}
}

void UIScreen::Close()
{

}