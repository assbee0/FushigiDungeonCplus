#pragma once
#include "UIScreen.h"

class HUD : public UIScreen
{
public:
	HUD(class Game* game);

	// Should be called when floor is changed to update the status
	void SetFloor(int f) { mFloor = f; UpdateValues(); }
	// Should be called when any of the values (except floor) are changed to update the status
	void SetStatus(int l, int c, int m, int a, int d, int e);

private:
	// Update the HUD text
	void UpdateValues();
	
	int mFloor;
	int mLevel;
	int mCurHp;
	int mMaxHp;
	int mAtk;
	int mDef;
	int mExp;
};