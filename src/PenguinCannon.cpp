#include "PenguinCannon.h"
#include <utility>
#include "Sprite.h"
#include "InputManager.h"
#include "Bullet.h"
#include "Game.h"
#include "Utils.h"
#include "Collider.h"
#include "Constants.h"

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) : Component(associated), pbody(std::move(penguinBody))
{
	associated.AddComponent(new Sprite(associated, "assets/img/cubngun.png"));
	associated.AddComponent(new Collider(associated));
}

void PenguinCannon::Update(float dt)
{
	timer.Update(dt);
	const auto body = pbody.lock();
	if (body == nullptr)
	{
		associated.RequestDelete();
		return;
	}

	associated.Box.CenterAt(body->Box.Center());

	auto input = InputManager::GetInstance();
	angle = (input.GetMouseMapPosition() - associated.Box.Center()).AngleD();
	associated.AngleDeg = angle;

	if (input.MousePress(LEFT_MOUSE_BUTTON))
	{
		Shoot();
	}
}

void PenguinCannon::Render()
{
}

bool PenguinCannon::Is(const std::string& type)
{
	return type == "PenguinCannon";
}

void PenguinCannon::NotifyCollision(GameObject& other)
{
}

void PenguinCannon::Shoot()
{
	if (timer.Get() < Constants::Penguin::SHOT_COOLDOWN)
	{
		return;
	}
	auto go = new GameObject();
	go->AddComponent(new Bullet(*go, Utils::Deg2Rad(angle), 300.f, 10, 2000.f, "assets/img/minionbullet2.png", false));
	go->Box.CenterAt(Vec2(60, 0).RotateD(angle) + associated.Box.Center());
	Game::GetInstance().GetState()->AddObject(go);
	timer.Restart();
}
