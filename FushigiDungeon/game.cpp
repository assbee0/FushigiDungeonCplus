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

Game::Game():
	mWindow(nullptr),
	mRenderer(nullptr),
	mGameState(GameState::GPlay),
	mIsUpdatingObjects(false),
	mPlayer(nullptr),
	mDungeon(nullptr),
	mCamera(nullptr),
	mLadder(nullptr),
	mFont(nullptr),
	mHUD(nullptr)
{

}
bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("FushigiDungeon", 400, 200, WINDOWS_WIDTH, WINDOWS_HEIGHT, SDL_WINDOW_OPENGL);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	if (!IMG_Init(IMG_INIT_PNG))
	{
		SDL_Log("Failed to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	if (TTF_Init())
	{
		SDL_Log("Failed to initialize SDL_ttf");
		return false;
	}

	Timer::deltaTime = 0;
	Timer::ticksCount = 0;

	LoadData();

	return true;
}

void Game::Loop()
//主循环
{
	while (mGameState != GameState::GQuit)
	{
		//处理包括输入的各种事件
		Event();
		//更新所有物体
		Update();
		//渲染所有物体
		Draw();
	}
}

void Game::Shutdown()
//结束并关闭游戏
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
	UnloadData();
	IMG_Quit();
	TTF_Quit();
}

void Game::CreateGameObject(GameObject* gameObject)
//创建GameObject并将其加入Game中
{
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
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

void Game::CreateEnemy(Enemy* enemy)
{
	mEnemies.emplace_back(enemy);
}

void Game::RemoveEnemy(Enemy* enemy)
{
	auto iter = std::find(mEnemies.begin(), mEnemies.end(), enemy);
	if (iter != mEnemies.end())
	{
		std::iter_swap(iter, mEnemies.end() - 1);
		mEnemies.pop_back();
	}
}

SDL_Texture* Game::GetTexture(const std::string& filename)
{
	SDL_Texture* tex = nullptr;
	auto iter = mTextures.find(filename);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	return tex;
}

void Game::PushUI(UIScreen* ui)
{
	mUIStack.emplace_back(ui);
}

void Game::NewFloor()
{
	while (!mEnemies.empty())
	{
		delete mEnemies.back();
	}
	mDungeon->NewFloor();
	Map* map = mDungeon->GetMap();

	mLadder->SetPosition(map->GetRandomPos());

	mPlayer->SetPosition(map->GetRandomPos());
	mPlayer->GetComponent<MoveComponent>()->SetMap(map);

	mCamera->SetPlayer(mPlayer);
	mCamera->SetMapW(map->width * 32);
	mCamera->SetMapH(map->height * 32);

	int curFloor = mDungeon->GetFloor();
	mHUD->SetFloor(curFloor);
	for (int i = 0; i < curFloor; i++)
	{
		Enemy* e1 = new Enemy(this);
		e1->SetPosition(map->GetRandomPos());
		e1->GetComponent<NavComponent>()->SetMap(map);
	}
	

}

void Game::Restart()
{
	UnloadData();
	LoadData();
	mGameState = GameState::GPlay;
}

void Game::Event()
//处理包括输入的各种事件
{
	SDL_Event event;
	bool mouseEnabled = false;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mGameState = GameState::GQuit;
			break;
		case SDL_KEYDOWN:
			if (mGameState == GameState::GPlay)
			{
				InputKeyPressed(event.key.keysym.sym);
				mPlayer->InputKeyPressed(event.key.keysym.sym); 
			}
			else if (mGameState == GameState::GPaused && !event.key.repeat)
			{
				if (!mUIStack.empty())
				{
					mouseEnabled = false;
					mUIStack.back()->InputKeyPressed(event.key.keysym.sym);
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (mGameState == GameState::GPaused)
			{
				if (!mUIStack.empty())
				{
					mUIStack.back()->InputKeyPressed(event.button.button);
				}
			}
			break;
		case SDL_MOUSEMOTION:
			if (mGameState == GameState::GPaused)
			{
				if (!mUIStack.empty())
				{
					mouseEnabled = true;
					mUIStack.back()->ResetButtonPointer();
				}
			}
			break;
		default:
			break;
		}
	}
	const Uint8* state = SDL_GetKeyboardState(NULL);
	
	if (mGameState == GameState::GPlay)
	{
		mPlayer->ProcessInput(state);
	}
	else if(!mUIStack.empty())
	{
		if (mouseEnabled)
		{
			mUIStack.back()->ProcessInput(state);
		}
	}

}

void Game::InputKeyPressed(int key)
{
	switch (key)
	{
	case SDLK_ESCAPE:
		new Menu(this);
		break;
	default:
		break;
	}
}

void Game::Update()
{
	Tick(50);

	mIsUpdatingObjects = true;
	for (auto gameObject : mGameObjects)
	{
		gameObject->UpdateGameObject();
	}
	for (auto gameObject : mGameObjects)
	{
		gameObject->LateUpdateGameObject();
	}
	mIsUpdatingObjects = false;

	for (auto pendingObject : mPendingObjects)
	{
		mGameObjects.emplace_back(pendingObject);
	}
	mPendingObjects.clear();

	std::vector<GameObject*> deadObjects;
	for (auto deadObject : mGameObjects)
	{
		if (deadObject->GetState() == GameObject::State::EDead)
		{
			deadObjects.emplace_back(deadObject);
		}
	}

	for (auto deadObject : deadObjects)
	{
		delete deadObject;
	}

	for (auto ui : mUIStack)
	{
		if (ui->GetState() == UIScreen::UIState::UActive)
		{
			ui->Update();
		}
	}

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
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);

	// Clear the buffer
	SDL_RenderClear(mRenderer);

	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer, mCamera);
	}

	for (auto ui : mUIStack)
	{
		ui->Draw(mRenderer);
	}

	// Swap the buffer
	SDL_RenderPresent(mRenderer);

}

void Game::Tick(int FPS)
//处理每帧时间，不够则等到达到指定FPS
{
	int fpsTime = 1000 / FPS;
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), Timer::ticksCount + fpsTime))
		SDL_Delay(1);

	Timer::deltaTime = (SDL_GetTicks() - Timer::ticksCount) / 1000.0f;

	Timer::ticksCount = SDL_GetTicks();
}

void Game::LoadData()
{
	LoadTexture("Sprites/Ground.png","Ground");
	LoadTexture("Sprites/Wall.png","Wall");
	LoadTexture("Sprites/chrA07.png","Player");
	LoadTexture("Sprites/SquareManWhite.png","Enemy1");
	LoadTexture("Sprites/ladder.png","Ladder");
	LoadTexture("Sprites/HUDbar.png","HUDbar");
	LoadTexture("Sprites/menuBackground.png", "MenuBack");
	LoadTexture("Sprites/ButtonOff.png", "ButtonOff");
	LoadTexture("Sprites/ButtonOn.png", "ButtonOn");
	LoadTexture("Sprites/GameOver.png", "GameOver");
	LoadFont("Font/Carlito-Regular.ttf", "Carlito");

	mDungeon = new Dungeon(this);
	mPlayer = new Player(this);
	Enemy* e1 = new Enemy(this);
	Camera* cam = new Camera(this);
	mCamera = cam->GetComponent<CameraLock>();
	mLadder = new Ladder(this);

	Map* map = mDungeon->GetMap();

	mLadder->SetPosition(map->GetRandomPos());

	mPlayer->SetPosition(map->GetRandomPos());
	mPlayer->GetComponent<MoveComponent>()->SetMap(map);

	e1->SetPosition(map->GetRandomPos());
	e1->GetComponent<NavComponent>()->SetMap(map);

	mCamera->SetPlayer(mPlayer);
	mCamera->SetMapW(map->width * 32);
	mCamera->SetMapH(map->height * 32);

	mHUD = new HUD(this);

	printf("Floor 1\n");
}

void Game::UnloadData()
{
	while (!mGameObjects.empty())
	{
		delete mGameObjects.back();
	}

	while (!mUIStack.empty())
	{
		delete mUIStack.back();
		mUIStack.pop_back();
	}

	for (auto tex : mTextures)
	{
		SDL_DestroyTexture(tex.second);
	}
	mTextures.clear();

	delete mFont;
}

void Game::LoadTexture(const std::string &filename)
{
	auto iter = mTextures.find(filename);
	if (iter != mTextures.end())
	{
		SDL_Log("Texture %s has been already loaded", filename.c_str());
	}
	else
	{
		SDL_Surface* surf = IMG_Load(filename.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", filename.c_str());
		}

		SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", filename.c_str());
		}

		mTextures.emplace(filename.c_str(), tex);
	}
}


void Game::LoadTexture(const std::string& filename, const std::string& newname)
{
	auto iter = mTextures.find(filename);
	if (iter != mTextures.end())
	{
		SDL_Log("Texture %s has been already loaded", filename.c_str());
	}
	else
	{
		SDL_Surface* surf = IMG_Load(filename.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", filename.c_str());
		}

		SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", filename.c_str());
		}

		mTextures.emplace(newname.c_str(), tex);
	}
}

void Game::LoadFont(const std::string& filename, const std::string& newname)
{
	Font* font = new Font(this);
	if (font->LoadFont(filename))
	{
		mFont = font;
	}
}