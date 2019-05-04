#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "State.h"
#include "Minion.h"
#include "Utils.h"
#include "Game.h"

Alien::Alien(GameObject& associated, int nMinions) : Component(associated), minionArray(nMinions)
{
	associated.AddComponent(new Sprite(associated, "assets/img/alien.png"));
}

Alien::~Alien()
{
	minionArray.clear();
}

void Alien::Start()
{
	auto state = Game::GetInstance().GetState();
	const auto currentGameObject = state->GetObjectPointer(&associated);
	static const float arcOffsetStep = (2.0f * PI) / minionArray.size();
	auto arcOffset = 0.f;
	for (auto& minion : minionArray)
	{
		auto go = new GameObject();
		go->AddComponent(new Minion(*go, currentGameObject, arcOffset));
		minion = state->AddObject(go);
		arcOffset += arcOffsetStep;
	}
}

void Alien::Update(float dt)
{
	if (hp <= 0)
	{
		associated.RequestDelete();
		return;
	}
	static const auto SPEED_MULTIPLIER = 500.f;
	auto& input = InputManager::GetInstance();
	auto& camera = Camera::pos;
	if (input.MousePress(LEFT_MOUSE_BUTTON))
	{
		taskQueue.emplace(Action::ActionType::SHOOT, float(input.GetMouseMapX()), float(input.GetMouseMapY()));
	}
	if (input.MousePress(RIGHT_MOUSE_BUTTON))
	{
		taskQueue.emplace(Action::ActionType::MOVE, float(input.GetMouseMapX()), float(input.GetMouseMapY()));
	}
	if (taskQueue.empty())
	{
		return;
	}
	auto& currentTask = taskQueue.front();
	switch (currentTask.type)
	{
	case Action::ActionType::MOVE:
	{
		if (speed.x == 0 && speed.y == 0)
		{
			speed = (currentTask.pos - associated.Box.Center()).Norm() * SPEED_MULTIPLIER;
		}
		auto movement = speed * dt;
		if (movement.Abs() >= (associated.Box.Center() - currentTask.pos).Abs())
		{
			speed = { 0,0 };
			associated.Box.CenterAt(currentTask.pos);
			taskQueue.pop();
		}
		else
		{
			associated.Box.x += movement.x;
			associated.Box.y += movement.y;
		}
		break;
	}
	case Action::ActionType::SHOOT:
	{
		taskQueue.pop();
		break;
	}
	default: taskQueue.pop();
	}
}

void Alien::Render()
{
}

bool Alien::Is(const std::string& type)
{
	return type == "alien";
}
