#include "UIScreen.h"
#include "Game.h"
#include "Font.h"

UIScreen::UIScreen(Game* game):
	mGame(game),
	mState(UIState::UActive),
	mBackPos(Vector2::Zero),
	mTexBackground(nullptr),
	mTextPos(Vector2::Zero),
	mButtonOff(nullptr),
	mButtonOn(nullptr),
	mText(nullptr),
	mTextCenter(true),
	mCurButton(nullptr)
{
	mGame->PushUI(this);
	mFont = mGame->GetFont();
}

UIScreen::~UIScreen()
{
	if (mText)
	{
		SDL_DestroyTexture(mText);
	}
	for (auto b : mButtons)
	{
		delete b;
	}
	mButtons.clear();
}

void UIScreen::ProcessInput(const uint8_t* state)
{
	if (!mButtons.empty())
	{
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		Vector2 mousePos = Vector2(static_cast<float>(mouseX), static_cast<float>(mouseY));

		for (auto b : mButtons)
		{
			if (b->ContainsMouse(mousePos))
			{
				b->SetIsSelected(true);
			}
			else
			{
				b->SetIsSelected(false);
			}
		}
	}
}

void UIScreen::InputKeyPressed(int key)
{
	switch (key)
	{
	case SDL_BUTTON_LEFT:
	case SDLK_SPACE:
	case SDLK_RETURN:
		if (!mButtons.empty())
		{
			for (auto b : mButtons)
			{
				if (b->GetIsSelected())
				{
					b->OnClick();
					break;
				}
			}
		}
		break;
	default:
		break;
	}
}

void UIScreen::Update()
{

}

void UIScreen::Draw(SDL_Renderer* renderer)
{
	SDL_Rect backRect = SDL_Rect();
	if (mTexBackground)
	{
		backRect = TextureRect(mTexBackground, mBackPos);
		SDL_RenderCopy(renderer, mTexBackground, nullptr, &backRect);
	}
	if (mText)
	{
		int w;
		int h;
		SDL_QueryTexture(mText, nullptr, nullptr, &w, &h);
		SDL_Rect dstrect;
		dstrect.w = w;
		dstrect.h = h;
		if (mTextCenter)
		{
			dstrect.x = backRect.x + backRect.w / 2 - w / 2;
			dstrect.y = backRect.y + backRect.h / 2 - h / 2;
		}
		else
		{
			dstrect.x = static_cast<int>(mTextPos.x - w / 2.0f);
			dstrect.y = static_cast<int>(mTextPos.y - h / 2.0f);
		}
		SDL_RenderCopy(renderer, mText, nullptr, &dstrect);
	}
	for (auto b : mButtons)
	{
		SDL_Texture* texB = nullptr;
		if (b->GetIsSelected())
			texB = mButtonOn;
		else
			texB = mButtonOff;
		SDL_Rect dstrect = TextureRect(texB, b->GetPosition());
		SDL_RenderCopy(renderer, texB, nullptr, &dstrect);

		SDL_Texture* texT = b->GetText();
		dstrect = TextureRect(texT, b->GetPosition());
		SDL_RenderCopy(renderer, texT, nullptr, &dstrect);
	}
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

void UIScreen::AddButton(Button* button)
{
	button->SetFont(mFont);
	int buttonW;
	int buttonH;
	SDL_QueryTexture(mButtonOff, nullptr, nullptr, &buttonW, &buttonH);
	button->SetWidthHeight(buttonW, buttonH);
	mButtons.emplace_back(button);
}

void UIScreen::ResetButtonState()
{
	for (auto b : mButtons)
	{
		b->SetIsSelected(false);
	}
}

void UIScreen::ResetButtonPointer()
{
	mCurButton = nullptr;
}

void UIScreen::Close()
{
	mState = UIState::UDead;
}

SDL_Rect UIScreen::TextureRect(SDL_Texture* tex, Vector2 pos)
{
	int w;
	int h;
	SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
	SDL_Rect dstrect;
	dstrect.w = w;
	dstrect.h = h;
	dstrect.x = static_cast<int>(pos.x - w / 2.0f);
	dstrect.y = static_cast<int>(pos.y - h / 2.0f);
	return dstrect;
}

Button::Button(UIScreen* ui):
	mOnClick(nullptr),
	mText(nullptr),
	mPosition(Vector2::Zero),
	mHeight(0),
	mWidth(0),
	mFont(nullptr),
	mIsSelected(false)
{
	ui->AddButton(this);
}

Button::~Button()
{
	if (mText)
	{
		SDL_DestroyTexture(mText);
	}
}

void Button::SetText(const std::string& text, const Vector3& color, int size, SDL_Renderer* renderer)
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

bool Button::ContainsMouse(Vector2 mouse)
{
	bool ifX = (mouse.x >= mPosition.x - mWidth / 2.0f && mouse.x <= mPosition.x + mWidth / 2.0f);
	bool ifY = (mouse.y >= mPosition.y - mHeight / 2.0f && mouse.y <= mPosition.y + mHeight / 2.0f);
	return ifX && ifY;
}

void Button::OnClick()
{
	if (mOnClick)
	{
		mOnClick();
	}
}