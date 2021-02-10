#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include <unordered_map>
#include "Math.h"

class Font
{
public:
	Font(class Game* game);
	~Font();

	bool LoadFont(const std::string& fileName);
	SDL_Surface* CreateText(const std::string& text, const Vector3& color, int size);

private:
	std::unordered_map<int, TTF_Font*> mFontData;
	class Game* mGame;
};