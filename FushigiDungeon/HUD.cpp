#include "HUD.h"
#include "Game.h"
#include <sstream>
#include <iomanip>

HUD::HUD(Game* game) :
	UIScreen(game),
	mFloor(1),
	mLevel(1),
	mCurHp(10),
	mMaxHp(10),
	mAtk(2),
	mDef(1),
	mExp(0)
{
	mTexBackground = game->GetTexture("HUDbar");
	SDL_SetTextureAlphaMod(mTexBackground, 128);
	UpdateValues();
}

void HUD::Draw(SDL_Renderer* renderer)
{
	SDL_Rect backRect = SDL_Rect();
	if (mTexBackground)
	{
		backRect.w = WINDOWS_WIDTH;
		backRect.h = 32;
		backRect.x = static_cast<int>(mBackPos.x);
		backRect.y = static_cast<int>(mBackPos.y);
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
			dstrect.x = static_cast<int>(mTextPos.x);
			dstrect.y = static_cast<int>(mTextPos.y);
		}
		SDL_RenderCopy(renderer, mText, nullptr, &dstrect);
	}
}

void HUD::UpdateValues()
{
	std::stringstream ss;
	ss << "Floor: " << std::setw(3) << std::setfill(' ') << mFloor << "     ";
	ss << "Level: " << std::setw(3) << std::setfill(' ') << mLevel << "     ";
	ss << "HP: " << std::setw(3) << std::setfill(' ') << mCurHp << 
		   " / " << std::setw(3) << std::setfill(' ') << mMaxHp << "     ";
	ss << "STR: " << std::setw(3) << std::setfill(' ') << mAtk << "     ";
	ss << "DEF: " << std::setw(3) << std::setfill(' ') << mDef << "     ";
	ss << "EXP: " << std::setw(5) << std::setfill(' ') << mExp;
	std::string str = ss.str();
	SetText(str, Vector3(1, 1, 1), 18, mGame->GetRenderer());
}

void HUD::SetStatus(int l, int c, int m, int a, int d, int e)
{
	mLevel = l;
	mCurHp = c;
	mMaxHp = m;
	mAtk = a;
	mDef = d;
	mExp = e;

	UpdateValues();
}