#include "PenguinBody.h"
#include "Sprite.h"
#include "PenguinCannon.h"
#include "Game.h"
#include "InputManager.h"
#include "Collider.h"
#include "Camera.h"
#include "Bullet.h"

PenguinBody* PenguinBody::player;

PenguinBody::PenguinBody(GameObject& associated): Component(associated)
{
	player = this;
	associated.AddComponent(new Sprite(associated, "assets/img/penguin.png"));
	associated.AddComponent(new Collider(associated));
}

PenguinBody::~PenguinBody()
{
	player = nullptr;
}

void PenguinBody::Start()
{
	const auto state = Game::GetInstance().GetState();
	auto go = new GameObject();
	go->AddComponent(new PenguinCannon(*go, state->GetObjectPointer(&associated)));
	pcannon = state->AddObject(go);
}

void PenguinBody::Update(float dt)
{
	if (hp <= 0)
	{
		associated.RequestDelete();
		Camera::Unfollow();
		return;
	}

	static const auto MAX_SPEED = 500.f;
	static const auto ACCELERATION = 200.f;
	static const auto ROTATION_SPEED = 100.f;
	auto input = InputManager::GetInstance();
	if (input.IsKeyDown(SDLK_w))
	{
		linearSpeed += ACCELERATION * dt;
		if (linearSpeed > MAX_SPEED)
		{
			linearSpeed = MAX_SPEED;
		}
	}
	if (input.IsKeyDown(SDLK_s))
	{
		linearSpeed -= ACCELERATION * dt;
		if (linearSpeed < -MAX_SPEED)
		{
			linearSpeed = -MAX_SPEED;
		}
	}
	if (input.IsKeyDown(SDLK_a))
	{
		angle -= ROTATION_SPEED * dt;
	}
	if (input.IsKeyDown(SDLK_d))
	{
		angle += ROTATION_SPEED * dt;
	}
	const auto movement = Vec2(linearSpeed, 0).RotateD(angle) * dt;
	associated.Box.x += movement.x;
	associated.Box.y += movement.y;
	associated.AngleDeg = angle;
}

void PenguinBody::Render()
{
}

bool PenguinBody::Is(const std::string& type)
{
	return type == "PenguinBody";
}

void PenguinBody::NotifyCollision(GameObject& other)
{
	const auto bullet = GET_COMPONENT(other, Bullet);
	if (bullet == nullptr || !bullet->targetsPlayer)
	{
		return;
	}
	hp -= bullet->GetDamage();
}
