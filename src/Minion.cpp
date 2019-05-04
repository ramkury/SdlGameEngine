#include "Minion.h"
#include "Sprite.h"
#include "Utils.h"
#include "Game.h"
#include "Bullet.h"

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) 
	: Component(associated), alienCenter(alienCenter), arc(arcOffsetDeg)
{
	associated.AddComponent(new Sprite(associated, "assets/img/minion.png"));
}

bool Minion::Is(const std::string& type)
{
	return type == "Minion";
}

void Minion::Shoot(Vec2 target) const
{
	const auto angle = (target - associated.Box.Center()).AngleR();
	auto go = new GameObject();
	go->AddComponent(new Bullet(*go, angle, 600.f, 10, 2000.f, "assets/img/minionbullet1.png"));
	go->Box.CenterAt(associated.Box.Center());
	Game::GetInstance().GetState()->AddObject(go);
}

void Minion::Update(float dt)
{
	static const float ANGULAR_SPEED = PI / 4.0f;
	const auto alien = alienCenter.lock();
	if (alien == nullptr)
	{
		associated.RequestDelete();
		return;
	}
	arc += ANGULAR_SPEED * dt;

	static const Vec2 STARTING_POSITION(200, 0);
	const auto currentPosition = STARTING_POSITION.RotateR(arc) + alien->Box.Center();
	associated.Box.CenterAt(currentPosition);
}

void Minion::Render()
{
}
