#include "Camera.h"
#include "InputManager.h"
#include <SDL2/SDL.h>

Vec2 Camera::pos;
Vec2 Camera::speed;
GameObject* Camera::focus = nullptr;

void Camera::Follow(GameObject* newFocus)
{
	focus = newFocus;
}

void Camera::Unfollow()
{
	focus = nullptr;
}

void Camera::Update(float dt)
{
	if (focus)
	{
		pos = focus->Box.Center();
		pos.x -= float(1024) / 2;
		pos.y -= float(600) / 2;
	}
	else
	{
		const double increment = 100.0f;
		speed = { 0, 0 };
		auto& input = InputManager::GetInstance();
		if (input.IsKeyDown(UP_ARROW_KEY))
		{
			speed.y -= increment;
		}
		if (input.IsKeyDown(DOWN_ARROW_KEY))
		{
			speed.y += increment;
		}
		if (input.IsKeyDown(RIGHT_ARROW_KEY))
		{
			speed.x += increment;
		}
		if (input.IsKeyDown(LEFT_ARROW_KEY))
		{
			speed.x -= increment;
		}
		pos += speed * dt;
	}
}
