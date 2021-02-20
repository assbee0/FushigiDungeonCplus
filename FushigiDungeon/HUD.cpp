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
	mExp(5)
{
	mTexBackground = game->GetTexture("HUDbar");
	SDL_SetTextureAlphaMod(mTexBackground, 128);
	mBackPos = Vector2(WINDOWS_WIDTH / 2, 16);
	UpdateValues();
}

void HUD::UpdateValues()
// Update the HUD text
{
	std::stringstream ss;
	ss << "Floor: " << std::setw(3) << std::setfill('0') << mFloor << "     ";
	ss << "Level: " << std::setw(3) << std::setfill('0') << mLevel << "     ";
	ss << "HP: " << std::setw(3) << std::setfill('0') << mCurHp << 
		   " / " << std::setw(3) << std::setfill('0') << mMaxHp << "     ";
	ss << "ATK: " << std::setw(3) << std::setfill('0') << mAtk << "     ";
	ss << "DEF: " << std::setw(3) << std::setfill('0') << mDef << "     ";
	ss << "NEXT EXP: " << std::setw(5) << std::setfill('0') << mExp;
	std::string str = ss.str();
	SetText(str, Vector3(0.286f, 0.141f, 0.055f), 18, mGame->GetRenderer());
}

void HUD::SetStatus(int l, int c, int m, int a, int d, int e)
// Should be called when any of the values are changed to update the status
{
	mLevel = l;
	mCurHp = c;
	mMaxHp = m;
	mAtk = a;
	mDef = d;
	mExp = e;

	UpdateValues();
}