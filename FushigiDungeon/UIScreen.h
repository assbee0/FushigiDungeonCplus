#pragma once
#include "SDL.h"
#include "Math.h"
#include <string>
#include <functional>
#include <vector>

class Button
{
public:
	Button(class UIScreen* ui);
	~Button();

	void SetText(const std::string& text, const Vector3& color, int size, SDL_Renderer* renderer);
	bool ContainsMouse(Vector2 mouse);
	void OnClick();

	void SetOnClick(std::function<void()> func) { mOnClick = func; }
	void SetFont(class Font* font) { mFont = font; }
	Vector2 GetPosition() const { return mPosition; }
	void SetPosition(Vector2 pos) { mPosition = pos; }
	void SetWidthHeight(int w, int h) { mWidth = w; mHeight = h; }
	SDL_Texture* GetText() const { return mText; }
	bool GetIsSelected() const { return mIsSelected; }
	void SetIsSelected(bool selected) { mIsSelected = selected; }

private:
	std::function<void()> mOnClick;
	SDL_Texture* mText;
	Vector2 mPosition;
	int mWidth;
	int mHeight;
	class Font* mFont;
	bool mIsSelected;
};

class UIScreen 
{
public:
	UIScreen(class Game* game);
	virtual ~UIScreen();

	virtual void ProcessInput(const uint8_t* state);
	virtual void InputKeyPressed(int key);
	virtual void Update();
	virtual void Draw(SDL_Renderer* renderer);
	void AddButton(class Button* button);
	void ResetButtonState();
	void ResetButtonPointer();
	void SetText(const std::string& text, const Vector3& color, int size, SDL_Renderer* renderer);

	enum class UIState 
	{ 
		UActive, 
		UPaused,
		UDead
	};
	void Close();

	UIState GetState() const { return mState; }

protected:
	SDL_Rect TextureRect(SDL_Texture* tex, Vector2 pos);

	class Game* mGame;
	UIState mState;

	SDL_Texture* mTexBackground;
	Vector2 mBackPos;
	SDL_Texture* mText;
	Vector2 mTextPos;
	SDL_Texture* mButtonOn;
	SDL_Texture* mButtonOff;
	class Font* mFont;
	bool mTextCenter;

	Button* mCurButton;
	std::vector<class Button*> mButtons;

private:
	Vector2 mPosition;
};