#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "SDL.h"

#define WINDOWS_WIDTH 640
#define WINDOWS_HEIGHT 480

class Game 
{
public:
	Game();
	bool Initialize();
	void Loop();
	void Shutdown();
	void CreateGameObject(class GameObject* gameObject);
	void RemoveGameObject(class GameObject* gameObject);
	void CreateSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	void CreateEnemy(class Enemy* enemy);
	void RemoveEnemy(class Enemy* enemy);
	SDL_Texture* GetTexture(const std::string &filename);
	void PushUI(class UIScreen* ui);
	void NewFloor();
	void Restart();

	enum class GameState
	{
		GPlay,
		GPaused,
		GQuit
	};

	GameState GetGameState() const { return mGameState; }
	void SetGameState(GameState state) { mGameState = state; }
	const std::vector<class UIScreen*>& GetUIStack() { return mUIStack; }
	const std::vector<class Enemy*>& GetEnemies() { return mEnemies; }
	SDL_Renderer* GetRenderer() { return mRenderer; }
	class Dungeon* GetDungeon() const { return mDungeon; }
	class Player* GetPlayer() const { return mPlayer; }
	class Ladder* GetLadder() const { return mLadder; }
	class HealthItem* GetHealthItem() { return mHealthItem; }
	void SetHealthItem() { mHealthItem = nullptr; }
	class Font* GetFont() const { return mFont; }
	class HUD* GetHUD() const { return mHUD; }

private:
	void Event();
	void InputKeyPressed(int key);
	void Update();
	void Draw();
	void Tick(int FPS);
	void LoadData();
	void UnloadData();
	void LoadTexture(const std::string& filename);
	void LoadTexture(const std::string& filename, const std::string& newname);
	void LoadFont(const std::string& filename, const std::string& newname);

	std::unordered_map<std::string, SDL_Texture*> mTextures;
	std::vector<class UIScreen*> mUIStack;

	std::vector<class GameObject*> mGameObjects;
	std::vector<class GameObject*> mPendingObjects;
	std::vector<class SpriteComponent*> mSprites;
	std::vector<class Enemy*> mEnemies;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	GameState mGameState;
	bool mIsUpdatingObjects;

	class Player* mPlayer;
	class Dungeon* mDungeon;
	class CameraLock* mCamera;
	class Ladder* mLadder;
	class HealthItem* mHealthItem;
	class Font* mFont;
	class HUD* mHUD;
};