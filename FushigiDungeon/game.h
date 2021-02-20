#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "SDL.h"
#include "SDL_mixer.h"

#define WINDOWS_WIDTH 640
#define WINDOWS_HEIGHT 480

class Game 
{
public:
	Game();
	bool Initialize();
	// Main Loop
	void Loop();
	// When quiting, unload and free the memory
	void Shutdown();
	// Create a game object and storage it
	void CreateGameObject(class GameObject* gameObject);
	// Remove gameObject from mPendingObjects or mGameObjects
	void RemoveGameObject(class GameObject* gameObject);
	// Create a sprite and add it into mSprites by drawOrder
	void CreateSprite(class SpriteComponent* sprite);
	// Remove sprite from mSprites
	void RemoveSprite(class SpriteComponent* sprite);
	// Add an enemy into mEnemies
	void CreateEnemy(class Enemy* enemy);
	// Remove enemy from mEnemies
	void RemoveEnemy(class Enemy* enemy);
	// Get texture from mTextures
	SDL_Texture* GetTexture(const std::string &filename);
	// Get music from mMusics
	Mix_Music* GetMusic(const std::string &filename);
	// Get sound from mSounds
	Mix_Chunk* GetSound(const std::string &filename);
	void PushUI(class UIScreen* ui);
	// Generate a map for new floor, and set game objects
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
	// Process input every frame
	void Event();
	// Process the key pressed when game state is GPlay
	void InputKeyPressed(int key);
	// Execute every frame
	void Update();
	// Draw every frame
	void Draw();
	// Control the frame rate to the requested frame rate FPS
	void Tick(int FPS);
	// Loading data, can be used for restarting the game
	// Load the gameobjects for floor 1
	void LoadData();
	// Unload the data when restarting the game or quiting the game
	void UnloadData();
	// Load the texture from file, and storage it into mTextures
	// Without changing the file name
	void LoadTexture(const std::string& filename);
	// Load the texture from file, and storage it into mTextures
	// Rename the texture as newname
	void LoadTexture(const std::string& filename, const std::string& newname);
	// Load the music from file, and storage it into mMusics
	// Rename the music as newname
	void LoadMusic(const std::string& filename, const std::string& newname);
	// Load the sound from file, and storage it into mSounds
	// Rename the sound as newname
	void LoadSound(const std::string& filename, const std::string& newname);
	// Load the sound from file, and storage it as mFont
	void LoadFont(const std::string& filename);

	std::unordered_map<std::string, SDL_Texture*> mTextures;
	std::unordered_map<std::string, Mix_Music*> mMusics;
	std::unordered_map<std::string, Mix_Chunk*> mSounds;
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