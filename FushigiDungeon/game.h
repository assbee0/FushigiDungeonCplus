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

	std::vector<class Enemy*> GetEnemies() const { return mEnemies; }
	class Dungeon* GetDungeon() const { return mDungeon; }
	class Player* GetPlayer() const { return mPlayer; }

private:
	void Event();
	void Update();
	void Draw();
	void Tick(int FPS);
	void LoadData();
	void UnloadData();
	void LoadTexture(const std::string& filename);
	void LoadTexture(const std::string& filename, const std::string& newname);

	std::unordered_map<std::string, SDL_Texture*> mTextures;

	std::vector<class GameObject*> mGameObjects;
	std::vector<class GameObject*> mPendingObjects;
	std::vector<class SpriteComponent*> mSprites;
	std::vector<class Enemy*> mEnemies;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	SDL_GLContext mContext;
	bool mIsRunning;
	bool mIsUpdatingObjects;

	class Player* mPlayer;
	class Dungeon* mDungeon;
	class CameraLock* mCamera;
};