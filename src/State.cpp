#include "State.h"
#include "SDL2/SDL.h"
#include "Face.h"
#include "Sound.h"
#include "Sprite.h"
#include "TileSet.h"
#include "TileMap.h"
#include "InputManager.h"

State::State() :
	music("assets/audio/stageState.ogg")
{
	auto background = new GameObject();
	background->AddComponent(new Sprite(*background, "assets/img/ocean.jpg"));
	objectArray.emplace_back(background);

	auto tiles = new GameObject();
	auto tileSet = new TileSet(*tiles, 64, 64, "assets/img/tileset.png");
	auto tileMap = new TileMap(*tiles, "assets/map/tileMap.txt", tileSet);
	tiles->AddComponent(tileMap);
	objectArray.emplace_back(tiles);

	music.Play();
}

State::~State()
{
	objectArray.clear();
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
	auto& input = InputManager::GetInstance();
	quitRequested = input.QuitRequested() || input.IsKeyDown(ESCAPE_KEY);

	if (input.KeyPress(SPACE_KEY))
	{
		const auto objPos = Vec2(200.f, 0.f).Rotate((rand() % 1440) / 4.f) + Vec2(float(input.GetMouseX()) , float(input.GetMouseY()));
		AddObject(int(objPos.x), int(objPos.y));
	}

	for (auto& go : objectArray)
	{
		go->Update(dt);
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

void State::AddObject(int mouseX, int mouseY)
{
	auto go = new GameObject();
	go->AddComponent(new Sprite(*go, "assets/img/penguinface.png"));
	go->Box.CenterAt(mouseX, mouseY);
	go->AddComponent(new Sound(*go, "assets/audio/boom.wav"));
	go->AddComponent(new Face(*go));
	objectArray.emplace_back(go);
}
