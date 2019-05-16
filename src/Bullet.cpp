#include "Bullet.h"
#include "Sprite.h"
#include "Utils.h"
#include "Collider.h"
#include "PenguinBody.h"
#include "Alien.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance,	const std::string& sprite, bool targetsPlayer)
	: Component(associated), targetsPlayer(targetsPlayer), distanceLeft(maxDistance), damage(damage)
{
	associated.AddComponent(new Sprite(associated, sprite, 3, 0.1));
	this->speed = Vec2(speed, 0).RotateR(angle);
	associated.AngleDeg = Utils::Rad2Deg(angle);
	associated.AddComponent(new Collider(associated));
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

void Bullet::NotifyCollision(GameObject& other)
{
	const auto bullet = GET_COMPONENT(other, Bullet);
	if (bullet != nullptr)
	{
		// Do nothing on collision with other bullets
		return;
	}
	if (targetsPlayer && GET_COMPONENT(other, PenguinBody) != nullptr)
	{
		associated.RequestDelete();
	}
	if (!targetsPlayer && GET_COMPONENT(other, Alien) != nullptr)
	{
		associated.RequestDelete();
	}
}

int Bullet::GetDamage() const
{
	return damage;
}
