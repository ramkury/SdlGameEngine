#include "StageState.h"
#include "SDL2/SDL.h"
#include "Sprite.h"
#include "TileSet.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "Collider.h"
#include "Collision.h"

StageState::StageState() :
	backgroundMusic("assets/audio/stageState.ogg")
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

	auto penguin = new GameObject();
	penguin->AddComponent(new PenguinBody(*penguin));
	penguin->Box.CenterAt(100	, 100);
	objectArray.emplace_back(penguin);

	Camera::Follow(penguin);

	backgroundMusic.Play();
}

StageState::~StageState()
{
	objectArray.clear();
}


void StageState::LoadAssets()
{
}

void StageState::Update(float dt)
{
	Camera::Update(dt);

	auto& input = InputManager::GetInstance();
	quitRequested = input.QuitRequested() || input.IsKeyDown(ESCAPE_KEY);

	UpdateArray(dt);

	for (size_t i = 0; i < objectArray.size(); i++)
	{
		for (size_t j = i + 1; j < objectArray.size(); j++)
		{
			auto& iGo = objectArray[i];
			auto iCollider = GET_COMPONENT(*iGo, Collider);
			if (iCollider == nullptr)
			{
				continue;
			}
			auto& jGo = objectArray[j];
			auto jCollider = GET_COMPONENT(*jGo, Collider);
			if (jCollider == nullptr)
			{
				continue;
			}
			if (Collision::IsColliding(iCollider->Box, jCollider->Box, iGo->AngleDeg, jGo->AngleDeg))
			{
				iGo->NotifyCollision(*jGo);
				jGo->NotifyCollision(*iGo);
			}
		}
	}
}

void StageState::Render()
{
	RenderArray();
}

void StageState::Start()
{
	if (started)
	{
		return;
	}
	LoadAssets();
	StartArray();
	started = true;
}

void StageState::Pause()
{
}

void StageState::Resume()
{
}
