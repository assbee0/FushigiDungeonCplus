#include "Game.h"
#include "SDL_image.h"
#include "NavComponent.h"
#include "Player.h"
#include "Enemy.h"
#include "Dungeon.h"
#include "Camera.h"
#include "CameraLock.h"
#include "MapComponent.h"
#include "MapMaker.h"
#include "Ladder.h"
#include "Timer.h"
#include "BattleComponent.h"
#include "HUD.h"
#include "Font.h"
#include "Menu.h"
#include "Random.h"
#include "HealthItem.h"

Game::Game():
	mWindow(nullptr),
	mRenderer(nullptr),
	mGameState(GameState::GPlay),
	mIsUpdatingObjects(false),
	mPlayer(nullptr),
	mDungeon(nullptr),
	mCamera(nullptr),
	mLadder(nullptr),
	mHealthItem(nullptr),
	mFont(nullptr),
	mHUD(nullptr)
{

}
bool Game::Initialize()
{
	// SDL library
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}
	// Init the window
	mWindow = SDL_CreateWindow("FushigiDungeon", 400, 200, WINDOWS_WIDTH, WINDOWS_HEIGHT, SDL_WINDOW_OPENGL);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	// Init the renderer
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	// SDL_image library
	if (!IMG_Init(IMG_INIT_PNG))
	{
		SDL_Log("Failed to initialize SDL_image: %s", SDL_GetError());
		return false;
	}
	// SDL_ttf library
	if (TTF_Init())
	{
		SDL_Log("Failed to initialize SDL_ttf");
		return false;
	}
	// SDL_mixer library
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		SDL_Log("Failed to initialize SDL_mixer");
		return false;
	}
	// Init the timer
	Timer::deltaTime = 0;
	Timer::ticksCount = 0;

	// Load all data from files, and init the first scene
	LoadData();

	return true;
}

void Game::Loop()
// Main Loop
{
	// When the game state is GQuit, break the loop
	while (mGameState != GameState::GQuit)
	{
		Event();
		Update();
		Draw();
	}
}

void Game::Shutdown()
// When quiting, unload and free the memory
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
	UnloadData();
	IMG_Quit();
	TTF_Quit();
	Mix_CloseAudio();
}

void Game::CreateGameObject(GameObject* gameObject)
// Create a game object and storage it
{
	// If game objects updating, add it to pending game objects
	if (mIsUpdatingObjects)
	{
		mPendingObjects.emplace_back(gameObject);
	}
	else
	{
		mGameObjects.emplace_back(gameObject);
	}
}

void Game::RemoveGameObject(GameObject* gameObject)
// Remove gameObject from mPendingObjects or mGameObjects
{
	auto iter = std::find(mPendingObjects.begin(), mPendingObjects.end(), gameObject);
	if (iter != mPendingObjects.end())
	{
		std::iter_swap(iter, mPendingObjects.end() - 1);
		mPendingObjects.pop_back();
	}

	iter = std::find(mGameObjects.begin(), mGameObjects.end(), gameObject);
	if (iter != mGameObjects.end())
	{
		std::iter_swap(iter, mGameObjects.end() - 1);
		mGameObjects.pop_back();
	}
}

void Game::CreateSprite(SpriteComponent* sprite)
// Create a sprite and add it into mSprites by drawOrder
{
	int order = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (order < (*iter)->GetDrawOrder())
		{
			break;
		}
	}
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
// Remove sprite from mSprites
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

void Game::CreateEnemy(Enemy* enemy)
// Add an enemy into mEnemies
{
	mEnemies.emplace_back(enemy);
}

void Game::RemoveEnemy(Enemy* enemy)
// Remove enemy from mEnemies
{
	auto iter = std::find(mEnemies.begin(), mEnemies.end(), enemy);
	if (iter != mEnemies.end())
	{
		std::iter_swap(iter, mEnemies.end() - 1);
		mEnemies.pop_back();
	}
}

SDL_Texture* Game::GetTexture(const std::string& filename)
// Get texture from mTextures
{
	SDL_Texture* tex = nullptr;
	auto iter = mTextures.find(filename);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	return tex;
}

Mix_Music* Game::GetMusic(const std::string& filename)
// Get music from mMusics
{
	Mix_Music* music = nullptr;
	auto iter = mMusics.find(filename);
	if (iter != mMusics.end())
	{
		music = iter->second;
	}
	return music;
}

Mix_Chunk* Game::GetSound(const std::string& filename)
// Get sound from mSounds
{
	Mix_Chunk* sound = nullptr;
	auto iter = mSounds.find(filename);
	if (iter != mSounds.end())
	{
		sound = iter->second;
	}
	return sound;
}

void Game::PushUI(UIScreen* ui)
{
	mUIStack.emplace_back(ui);
}

void Game::NewFloor()
// Generate a map for new floor, and set game objects
{
	// Free the enemies last floor
	while (!mEnemies.empty())
	{
		delete mEnemies.back();
	}
	mEnemies.clear();
	// Free the health item last floor
	if (mHealthItem)
	{
		delete mHealthItem;
	}
	
	// Generate the map of new floor
	mDungeon->NewFloor();
	Map* map = mDungeon->GetMap();
	// Set ladder to a random place
	mLadder->SetPosition(map->GetRandomPos());
	// Set player to a random place, and give it map information for moving
	mPlayer->SetPosition(map->GetRandomPos());
	mPlayer->GetComponent<MoveComponent>()->SetDst(mPlayer->GetPosition());
	mPlayer->GetComponent<MoveComponent>()->SetMap(map);
	// Bring new map information to the camera
	mCamera->SetPlayer(mPlayer);
	mCamera->SetMapW(map->width * 32);
	mCamera->SetMapH(map->height * 32);

	int curFloor = mDungeon->GetFloor();
	// Update the floor information in HUD
	mHUD->SetFloor(curFloor);
	// Generate enemies according to current floor
	for (int i = 0; i < curFloor; i++)
	{
		int enemyNumber;
		// Random generate enemy index
		enemyNumber = Random::GetIntRange(Mathf::Max(curFloor / 3 - 1, 1), curFloor / 3 + 1);
		// There are 6 types of enemies
		if (enemyNumber > 6)
			enemyNumber = 6;
		// Instiate the enemy, set it to a random place, and give it map information for moving
		Enemy* e1 = new Enemy(this, enemyNumber);
		e1->SetPosition(map->GetRandomPos());
		e1->GetComponent<NavComponent>()->SetMap(map);
	}
	
	// Generate the health item at current floor
	// 1 item for 1 floor, and 80% to be a herb, 20% to be a aid box
	int random = Random::GetIntRange(1, 5);
	if(random == 5)
		mHealthItem = new HealthItem(this, 2);
	else
		mHealthItem = new HealthItem(this, 1);
	mHealthItem->SetPosition(map->GetRandomPos());

}

void Game::Restart()
{
	UnloadData();
	LoadData();
	mGameState = GameState::GPlay;
	// When the menu unloaded it can't play the sound, so play here
	Mix_PlayChannel(-1, GetSound("Menu"), 0);
}

void Game::Event()
// Process input every frame
{
	SDL_Event event;
	// Control if the mouse input can be received
	bool mouseEnabled = false;
	// If there are events, process all of them
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// Quit event, such as click the x in the window
		case SDL_QUIT:
			mGameState = GameState::GQuit;
			break;
			// Keyboard pressed
		case SDL_KEYDOWN:
			// When GPlay process the key pressed for game and player
			if (mGameState == GameState::GPlay)
			{
				InputKeyPressed(event.key.keysym.sym);
				mPlayer->InputKeyPressed(event.key.keysym.sym); 
			}
			// When GPaused process the key pressed for the UI on the top of the stack
			else if (mGameState == GameState::GPaused && !event.key.repeat)
			{
				if (!mUIStack.empty())
				{
					// Disable the mouse input
					mouseEnabled = false;
					mUIStack.back()->InputKeyPressed(event.key.keysym.sym);
				}
			}
			break;
			// Mouse pressed
		case SDL_MOUSEBUTTONDOWN:
			// When GPaused process the mouse pressed for the UI on the top of the stack
			if (mGameState == GameState::GPaused)
			{
				if (!mUIStack.empty())
				{
					mUIStack.back()->InputKeyPressed(event.button.button);
				}
			}
			break;
			// Mouse moved
		case SDL_MOUSEMOTION:
			// When GPaused process the mouse move for the UI on the top of the stack
			if (mGameState == GameState::GPaused)
			{
				if (!mUIStack.empty())
				{
					// Awaken mouse input
					mouseEnabled = true;
					// Reset the state of button selected to init state
					mUIStack.back()->ResetButtonPointer();
				}
			}
			break;
		default:
			break;
		}
	}

	// Process the state of input current frame
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// When GPlay, process the player
	if (mGameState == GameState::GPlay)
	{
		mPlayer->ProcessInput(state);
	}
	// When GPaused, process the UI
	else if(!mUIStack.empty())
	{
		if (mouseEnabled)
		{
			mUIStack.back()->ProcessInput(state);
		}
	}

}

void Game::InputKeyPressed(int key)
// Process the key pressed when game state is GPlay
{
	switch (key)
	{
		// When Pressing Escape, call menu
	case SDLK_ESCAPE:
		new Menu(this);
		break;
	default:
		break;
	}
}

void Game::Update()
// Execute every frame
{
	// Set the max frame rate to 50
	Tick(50);

	// Update all game objects
	mIsUpdatingObjects = true;
	for (auto gameObject : mGameObjects)
	{
		gameObject->UpdateGameObject();
	}
	// Late update all game objects (main for camera)
	for (auto gameObject : mGameObjects)
	{
		gameObject->LateUpdateGameObject();
	}
	mIsUpdatingObjects = false;
	// Move all the pending objects to mGameOjects
	for (auto pendingObject : mPendingObjects)
	{
		mGameObjects.emplace_back(pendingObject);
	}
	mPendingObjects.clear();
	// Move all the game objects that have been set to EDead to deadObjects
	std::vector<GameObject*> deadObjects;
	for (auto deadObject : mGameObjects)
	{
		if (deadObject->GetState() == GameObject::State::EDead)
		{
			deadObjects.emplace_back(deadObject);
		}
	}
	// Free all dead objects
	for (auto deadObject : deadObjects)
	{
		delete deadObject;
	}

	// Update active UIs
	for (auto ui : mUIStack)
	{
		if (ui->GetState() == UIScreen::UIState::UActive)
		{
			ui->Update();
		}
	}
	// Free all dead UIs
	for (auto iter = mUIStack.begin(); iter != mUIStack.end(); iter++)
	{
		if ((*iter)->GetState() == UIScreen::UIState::UDead)
		{
			delete *iter;
			iter = mUIStack.erase(iter);
			iter--;
		}
	}
}

void Game::Draw()
// Draw every frame
{
	// Background color
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);

	// Clear the buffer
	SDL_RenderClear(mRenderer);

	// Render all sprites
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer, mCamera);
	}
	// Render all UIs
	for (auto ui : mUIStack)
	{
		ui->Draw(mRenderer);
	}

	// Swap the buffer
	SDL_RenderPresent(mRenderer);

}

void Game::Tick(int FPS)
// Control the frame rate to the requested frame rate FPS
{
	// The time per frame
	int fpsTime = 1000 / FPS;
	// If the time of last frame is less than requested, then wait
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), Timer::ticksCount + fpsTime))
		SDL_Delay(1);

	// The time of last frame
	Timer::deltaTime = (SDL_GetTicks() - Timer::ticksCount) / 1000.0f;
	// Total time cost
	Timer::ticksCount = SDL_GetTicks();
}

void Game::LoadData()
// Loading data, can be used for restarting the game
// Load the gameobjects for floor 1
{
	// Load and rename the textures, font, musics, and sounds
	LoadTexture("Sprites/Ground.spr","Ground");
	LoadTexture("Sprites/Wall.spr","Wall");
	LoadTexture("Sprites/Player.spr","Player");
	LoadTexture("Sprites/SquareManWhite.spr","SquareManWhite");
	LoadTexture("Sprites/SquareManGreen.spr","SquareManGreen");
	LoadTexture("Sprites/SquareManYellow.spr","SquareManYellow");
	LoadTexture("Sprites/SquareManBlue.spr","SquareManBlue");
	LoadTexture("Sprites/SquareManRed.spr","SquareManRed");
	LoadTexture("Sprites/SquareManBlack.spr","SquareManBlack");
	LoadTexture("Sprites/ladder.spr","Ladder");
	LoadTexture("Sprites/Yakusou.spr","Yakusou");
	LoadTexture("Sprites/HpBox.spr","HpBox");
	LoadTexture("Sprites/HUDbar.spr","HUDbar");
	LoadTexture("Sprites/menuBackground.spr", "MenuBack");
	LoadTexture("Sprites/MessageBox.spr", "MessageBack");
	LoadTexture("Sprites/ButtonOff.spr", "ButtonOff");
	LoadTexture("Sprites/ButtonOffS.spr", "ButtonOffS");
	LoadTexture("Sprites/ButtonOn.spr", "ButtonOn");
	LoadTexture("Sprites/ButtonOnS.spr", "ButtonOnS");
	LoadTexture("Sprites/GameOver.spr", "GameOver");
	LoadTexture("Sprites/GameClear.spr", "GameClear");
	LoadTexture("Sprites/Tutorial.spr", "Tutorial");
	LoadFont("Font/Carlito-Regular.ttf");
	LoadMusic("Music/Dungeon1.mp3","Dungeon1");
	LoadMusic("Music/Dungeon2.mp3","Dungeon2");
	LoadMusic("Music/Dungeon3.mp3","Dungeon3");
	LoadMusic("Music/Dungeon4.mp3","Dungeon4");
	LoadMusic("Music/Victory.mp3","Victory");
	LoadMusic("Music/Defeat.mp3","Defeat");
	LoadSound("Sound/Attack1.wav","Attack1");
	LoadSound("Sound/Attack2.wav","Attack2");
	LoadSound("Sound/Attack3.mp3","Attack3");
	LoadSound("Sound/Cancel.wav","Cancel");
	LoadSound("Sound/Menu.wav","Menu");
	LoadSound("Sound/Stairs.wav","Stairs");
	LoadSound("Sound/LevelUp.mp3","LevelUp");
	LoadSound("Sound/Cure1.mp3","Cure1");
	LoadSound("Sound/Cure2.mp3","Cure2");

	// Play the bgm for floor 1 to 6
	Mix_PlayMusic(GetMusic("Dungeon1"), -1);
	Mix_VolumeMusic(64);

	// Instantiate the game objects
	mDungeon = new Dungeon(this);
	mPlayer = new Player(this);
	Enemy* e1 = new Enemy(this, 1);
	Camera* cam = new Camera(this);
	mCamera = cam->GetComponent<CameraLock>();
	mLadder = new Ladder(this);

	Map* map = mDungeon->GetMap();

	// Set the positions for ladder, player, and enemies
	mLadder->SetPosition(map->GetRandomPos());
	mPlayer->SetPosition(map->GetRandomPos());
	mPlayer->GetComponent<MoveComponent>()->SetMap(map);
	e1->SetPosition(map->GetRandomPos());
	e1->GetComponent<NavComponent>()->SetMap(map);

	// Bring the player position and map information to the camera for coordinate transform
	mCamera->SetPlayer(mPlayer);
	mCamera->SetMapW(map->width * 32);
	mCamera->SetMapH(map->height * 32);

	mHUD = new HUD(this);

	printf("Floor 1\n");
}

void Game::UnloadData()
// Unload the data when restarting the game or quiting the game
{
	// Unload the game objects
	while (!mGameObjects.empty())
	{
		delete mGameObjects.back();
	}

	// Unload UI
	while (!mUIStack.empty())
	{
		delete mUIStack.back();
		mUIStack.pop_back();
	}

	// Unload textures
	for (auto tex : mTextures)
	{
		SDL_DestroyTexture(tex.second);
	}
	mTextures.clear();

	// Unload bgms
	for (auto music : mMusics)
	{
		Mix_FreeMusic(music.second);
	}
	mMusics.clear();

	// Unload sounds
	for (auto sound : mSounds)
	{
		Mix_FreeChunk(sound.second);
	}
	mSounds.clear();

	// Unload the font
	delete mFont;
}

void Game::LoadTexture(const std::string &filename)
// Load the texture from file, and storage it into mTextures
// Without changing the file name
{
	auto iter = mTextures.find(filename);
	if (iter != mTextures.end())
	{
		SDL_Log("Texture %s has been already loaded", filename.c_str());
	}
	else
	{
		// Load the image file to surface
		SDL_Surface* surf = IMG_Load(filename.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", filename.c_str());
		}
		// Transform the surface to texture
		SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", filename.c_str());
		}
		// Add the texture to mTextures
		mTextures.emplace(filename.c_str(), tex);
	}
}


void Game::LoadTexture(const std::string& filename, const std::string& newname)
// Load the texture from file, and storage it into mTextures
// Rename the texture as newname
{
	// Load the image file to surface
	SDL_Surface* surf = IMG_Load(filename.c_str());
	if (!surf)
	{
		SDL_Log("Failed to load texture file %s", filename.c_str());
	}
	// Transform the surface to texture
	SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surf);
	SDL_FreeSurface(surf);
	if (!tex)
	{
		SDL_Log("Failed to convert surface to texture for %s", filename.c_str());
	}
	// Add the texture to mTextures
	mTextures.emplace(newname.c_str(), tex);
}

void Game::LoadMusic(const std::string& filename, const std::string& newname)
// Load the music from file, and storage it into mMusics
// Rename the music as newname
{
	
	Mix_Music* music;
	music = Mix_LoadMUS(filename.c_str());
	if (!music)
	{
		SDL_Log("Failed to load music file %s", filename.c_str());
	}
	mMusics.emplace(newname.c_str(), music);
}

void Game::LoadSound(const std::string& filename, const std::string& newname)
// Load the sound from file, and storage it into mSounds
// Rename the sound as newname
{

	Mix_Chunk* sound;
	sound = Mix_LoadWAV(filename.c_str());
	if (!sound)
	{
		SDL_Log("Failed to load music file %s", filename.c_str());
	}
	mSounds.emplace(newname.c_str(), sound);
}

void Game::LoadFont(const std::string& filename)
// Load the sound from file, and storage it as mFont
{
	Font* font = new Font(this);
	if (font->LoadFont(filename))
	{
		mFont = font;
	}
}