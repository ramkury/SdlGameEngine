#include "Collider.h"

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated), scale(scale), offset(offset)
{
}

void Collider::Update(float dt)
{
	Box = associated.Box;
	Box.w *= scale.x;
	Box.h *= scale.y;
	Box.CenterAt(associated.Box.Center() + offset.RotateD(associated.AngleDeg));
}

void Collider::Render()
{
}

bool Collider::Is(const std::string& type)
{
	return type == "Collider";
}

void Collider::SetScale(Vec2 scale)
{
	this->scale = scale;
}

void Collider::SetOffset(Vec2 offset)
{
	this->offset = offset;
}
