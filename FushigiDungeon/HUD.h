#pragma once
#include "UIScreen.h"

class HUD : public UIScreen
{
public:
	HUD(class Game* game);

	void SetFloor(int f) { mFloor = f; UpdateValues(); }
	void SetStatus(int l, int c, int m, int a, int d, int e);

private:
	void UpdateValues();
	
	int mFloor;
	int mLevel;
	int mCurHp;
	int mMaxHp;
	int mAtk;
	int mDef;
	int mExp;
};