#include "Alien.h"
#include "Sprite.h"
#include "Camera.h"
#include "State.h"
#include "Minion.h"
#include "Utils.h"
#include "Game.h"
#include "Collider.h"
#include "Bullet.h"
#include "Constants.h"
#include "PenguinBody.h"
#include "Sound.h"

int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int nMinions) : Component(associated), minionArray(nMinions)
{
	alienCount++;
	associated.AddComponent(new Sprite(associated, "assets/img/alien.png"));
	associated.AddComponent(new Collider(associated));
}

Alien::~Alien()
{
	minionArray.clear();
	alienCount--;
}

void Alien::Start()
{
	auto state = Game::GetInstance().GetState();
	const auto currentGameObject = state->GetObjectPointer(&associated);
	static const float ARC_OFFSET_STEP = (2.0f * PI) / minionArray.size();
	auto arcOffset = 0.f;
	for (auto& minion : minionArray)
	{
		auto go = new GameObject();
		go->AddComponent(new Minion(*go, currentGameObject, arcOffset));
		minion = state->AddObject(go);
		arcOffset += ARC_OFFSET_STEP;
	}
}

void Alien::Update(float dt)
{
	if (hp <= 0)
	{
		Die();
		return;
	}

	associated.AngleDeg -= Constants::Alien::ROTATION_SPEED * dt;

	if (PenguinBody::player == nullptr)
	{
		return;
	}

	switch (state)
	{
	case MOVING:
		{
			if (associated.Box.Center().DistanceTo(destination) <= speed.Abs() * dt)
			{
				// Reached the destination
				associated.Box.CenterAt(destination);
				Shoot(PenguinBody::player->GetPosition());
				restTimer.Restart();
				state = RESTING;
			}
			else
			{
				associated.Box.Translate(speed * dt);
			}
			break;
		}
	case RESTING:
		{
			restTimer.Update(dt);
			if (restTimer.Get() >= Constants::Alien::REST_TIME)
			{
				destination = PenguinBody::player->GetPosition();
				speed = (destination - associated.Box.Center()).Norm() * Constants::Alien::MOVEMENT_SPEED;
				state = MOVING;
			}
			break;
		};
	default: break;
	}
}

void Alien::Render()
{
}

bool Alien::Is(const std::string& type)
{
	return type == "Alien";
}

void Alien::NotifyCollision(GameObject& other)
{
	const auto bullet = GET_COMPONENT(other, Bullet);
	if (bullet == nullptr || bullet->targetsPlayer)
	{
		return;
	}
	hp -= bullet->GetDamage();
}

void Alien::Shoot(Vec2 target)
{
	float dist = INFINITY;
	std::shared_ptr<GameObject> shooter;
	for (auto && minion : minionArray)
	{
		const auto currentObject = minion.lock();
		const auto currentDistance = currentObject->Box.Center().DistanceTo(target);
		if (currentDistance < dist)
		{
			dist = currentDistance;
			shooter = currentObject;
		}
	}

	const auto minion = GET_COMPONENT(*shooter, Minion);
	minion->Shoot(target);
}

void Alien::Die()
{
	auto explosion = new GameObject();
	explosion->AddComponent(new Sprite(*explosion, "assets/img/aliendeath.png", 4, 0.25, 1));
	auto sound = new Sound(*explosion, "assets/audio/boom.wav");
	explosion->AddComponent(sound);
	sound->Play();
	explosion->Box.CenterAt(associated.Box.Center());
	Game::GetInstance().GetState()->AddObject(explosion);

	associated.RequestDelete();
}
