#pragma once
#include "SDL.h"
#include "Time.h"
#include <string>
#include <vector>
#include <unordered_map>
#include "GameObject.h"

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
	SDL_Texture* GetTexture(const std::string &filename);

	std::vector<class Enemy*> GetEnemies() { return mEnemies; }

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
	bool mIsRunning;
	bool mIsUpdatingObjects;

	class Player* mPlayer;
	class Dungeon* mDungeon;
};