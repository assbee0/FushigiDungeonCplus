#pragma once
#include "SDL.h"
#include "Math.h"
#include <string>

class UIScreen 
{
public:
	UIScreen(class Game* game);
	~UIScreen();

	virtual void ProcessInput(const uint8_t* state);
	virtual void Update();
	virtual void Draw(SDL_Renderer* renderer);
	void SetText(const std::string& text, const Vector3& color, int size, SDL_Renderer* renderer);

	enum class UIState 
	{ 
		UActive, 
		UDead
	};
	void Close();

	UIState GetState() const { return mState; }

protected:
	class Game* mGame;
	UIState mState;

	SDL_Texture* mTexBackground;
	Vector2 mBackPos;
	SDL_Texture* mText;
	Vector2 mTextPos;
	class Font* mFont;

	bool mTextCenter;

private:
	Vector2 mPosition;
};