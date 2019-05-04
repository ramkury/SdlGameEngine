#include "PenguinCannon.h"
#include <utility>
#include "Sprite.h"
#include "InputManager.h"
#include "Bullet.h"
#include "Game.h"
#include "Utils.h"

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) : Component(associated), pbody(std::move(penguinBody))
{
	associated.AddComponent(new Sprite(associated, "assets/img/cubngun.png"));
}

void PenguinCannon::Update(float dt)
{
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

void PenguinCannon::Shoot() const
{
	auto go = new GameObject();
	go->AddComponent(new Bullet(*go, Utils::Deg2Rad(angle), 300.f, 10, 2000.f, "assets/img/minionbullet2.png"));
	go->Box.CenterAt(Vec2(60, 0).RotateD(angle) + associated.Box.Center());
	Game::GetInstance().GetState()->AddObject(go);
}
