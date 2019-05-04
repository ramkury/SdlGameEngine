#include "Bullet.h"
#include "Sprite.h"
#include "Utils.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance,	const std::string& sprite)
	: Component(associated), distanceLeft(maxDistance), damage(damage)
{
	associated.AddComponent(new Sprite(associated, sprite, 3, 0.1));
	this->speed = Vec2(speed, 0).RotateR(angle);
	associated.AngleDeg = Utils::Rad2Deg(angle);
}

void Bullet::Update(float dt)
{
	const auto movement = speed * dt;
	associated.Box.x += movement.x;
	associated.Box.y += movement.y;
	distanceLeft -= movement.Abs();
	if (distanceLeft <= 0)
	{
		associated.RequestDelete();
	}
}

void Bullet::Render()
{
}

bool Bullet::Is(const std::string& type)
{
	return type == "Bullet";
}

int Bullet::GetDamage() const
{
	return damage;
}
