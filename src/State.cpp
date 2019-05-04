#include "State.h"
#include "SDL2/SDL.h"
#include "Sprite.h"
#include "TileSet.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"

State::State() :
	music("assets/audio/stageState.ogg")
{
	auto background = new GameObject();
	background->AddComponent(new Sprite(*background, "assets/img/ocean.jpg"));
	background->AddComponent(new CameraFollower(*background));
	objectArray.emplace_back(background);

	auto tiles = new GameObject();
	auto tileSet = new TileSet(*tiles, 64, 64, "assets/img/tileset.png");
	auto tileMap = new TileMap(*tiles, "assets/map/tileMap.txt", tileSet);
	tiles->AddComponent(tileMap);
	objectArray.emplace_back(tiles);

	auto alien = new GameObject();
	alien->AddComponent(new Alien(*alien, 4));
	alien->Box.CenterAt(512, 300);
	objectArray.emplace_back(alien);

	music.Play();
}

State::~State()
{
	objectArray.clear();
}

void State::Start()
{
	if (started)
	{
		return;
	}

	LoadAssets();
	for (auto& go : objectArray)
	{
		go->Start();
	}
	started = true;
}

bool State::QuitRequested()
{
	return quitRequested;
}

void State::LoadAssets()
{
}

void State::Update(float dt)
{
	Camera::Update(dt);

	auto& input = InputManager::GetInstance();
	quitRequested = input.QuitRequested() || input.IsKeyDown(ESCAPE_KEY);

	for (size_t i = 0; i < objectArray.size(); ++i)
	{
		objectArray[i]->Update(dt);
	}
	for (int i = objectArray.size() - 1; i >= 0; i--)
	{
		if (objectArray[i]->IsDead())
		{
			objectArray.erase(objectArray.begin() + i);
		}
	}
}

void State::Render()
{
	for (auto& go : objectArray)
	{
		go->Render();
	}
}

//void State::AddObject(int mouseX, int mouseY)
//{
//	auto go = new GameObject();
//	go->AddComponent(new Sprite(*go, "assets/img/penguinface.png"));
//	go->Box.CenterAt(mouseX + Camera::pos.x, mouseY + Camera::pos.y);
//	go->AddComponent(new Sound(*go, "assets/audio/boom.wav"));
//	go->AddComponent(new Face(*go));
//	objectArray.emplace_back(go);
//}

std::weak_ptr<GameObject> State::AddObject(GameObject* go)
{
	objectArray.emplace_back(go);
	if (started)
	{
		go->Start();
	}
	return objectArray.back();
}

std::weak_ptr<GameObject> State::GetObjectPointer(GameObject* go)
{
	for (auto& ptr : objectArray)
	{
		if (ptr.get() == go)
		{
			return ptr;
		}
	}
	return std::weak_ptr<GameObject>();
}
