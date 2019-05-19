#include "Collider.h"
#include "Utils.h"

#ifdef _DEBUG
#define DEBUG
#endif // _DEBUG

#ifdef DEBUG
#include "Camera.h"
#include "Game.h"
#include <SDL2/SDL.h>
#endif // DEBUG

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

void Collider::Render() {
#ifdef DEBUG
	const Vec2 center(Box.Center());
	SDL_Point points[5];

	Vec2 point = (Vec2(Box.x, Box.y) - center).RotateD(associated.AngleDeg) + center - Camera::pos;
	points[0] = { int(point.x), int(point.y )};
	points[4] = { int(point.x), int(point.y )};

	point = (Vec2(Box.x + Box.w, Box.y) - center).RotateD(associated.AngleDeg) + center - Camera::pos;
	points[1] = { int(point.x), int(point.y )};

	point = (Vec2(Box.x + Box.w, Box.y + Box.h) - center).RotateD(associated.AngleDeg) + center - Camera::pos;
	points[2] = { int(point.x), int(point.y )};

	point = (Vec2(Box.x, Box.y + Box.h) - center).RotateD(associated.AngleDeg) + center - Camera::pos;
	points[3] = { int(point.x), int(point.y )};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
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
