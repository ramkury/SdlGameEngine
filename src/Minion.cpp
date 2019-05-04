#include "Minion.h"
#include "Sprite.h"
#include "Utils.h"

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) 
	: Component(associated), alienCenter(alienCenter), arc(arcOffsetDeg)
{
	associated.AddComponent(new Sprite(associated, "assets/img/minion.png"));
}

bool Minion::Is(const std::string& type)
{
	return type == "minion";
}

void Minion::Shoot(Vec2 target)
{

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
