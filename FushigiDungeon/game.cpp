#include "Game.h"
#include "SDL_image.h"
#include "SpriteComponent.h"
#include "Player.h"
#include "Dungeon.h"

Game::Game():
	mWindow(nullptr),
	mRenderer(nullptr),
	mIsRunning(true),
	mIsUpdatingObjects(false),
	mPlayer(nullptr)
{

}
bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("FushigiDungeon", 400, 200, 640, 480, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

	Time::deltaTime = 0;
	Time::ticksCount = 0;

	LoadData();

	return true;
}

void Game::Loop()
//主循环
{
	while (mIsRunning)
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
	IMG_Quit();
	UnloadData();
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

void Game::Event()
//处理包括输入的各种事件
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			mIsRunning = false;
			break;
		}
	}
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
	
	mPlayer->ProcessInput(state);
}

void Game::Update()
{
	Tick(60);

	mIsUpdatingObjects = true;
	for (auto gameObject : mGameObjects)
	{
		gameObject->UpdateGameObject();
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
}

void Game::Draw()
{
	SDL_SetRenderDrawColor(
		mRenderer,
		0,		// R
		0,		// G 
		255,	// B
		255		// A
	);

	// 清除当前buffer
	SDL_RenderClear(mRenderer);

	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	// 交换buffer
	SDL_RenderPresent(mRenderer);
}

void Game::Tick(int FPS)
//处理每帧时间，不够则等到达到指定FPS
{
	int fpsTime = 1000 / FPS;
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), Time::ticksCount + fpsTime))
		;

	Time::deltaTime = (SDL_GetTicks() - Time::ticksCount) / 1000.0f;

	Time::ticksCount = SDL_GetTicks();
}

void Game::LoadData()
{
	LoadTexture("Sprites/Ground.png","Ground");
	LoadTexture("Sprites/Wall.png","Wall");
	LoadTexture("Sprites/chrA07.png","Player");

	mDungeon = new Dungeon(this);

	mPlayer = new Player(this);
	mPlayer->SetPosition(Vector2(320, 256));
	mPlayer->SetMap(mDungeon->GetMap());

}

void Game::UnloadData()
{
	while (!mGameObjects.empty())
	{
		delete mGameObjects.back();
	}
	for (auto tex : mTextures)
	{
		SDL_DestroyTexture(tex.second);
	}
	mTextures.clear();
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