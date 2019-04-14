#include "Face.h"
#include "Sound.h"
#include "InputManager.h"
#include <SDL2/SDL_mouse.h>
#include "Camera.h"

Face::Face(GameObject & associated) : Component(associated), hitpoints(30)
{
}

void Face::Damage(int damage)
{
	hitpoints -= damage;
	if (hitpoints <= 0)
	{
		associated.RequestDelete();
		const auto sound = associated.GetComponent("sound");
		if (sound != nullptr)
		{
			std::dynamic_pointer_cast<Sound>(sound)->Play(1);
		}
	}
}

void Face::Update(float dt)
{
	auto& input = InputManager::GetInstance();
	if (input.MousePress(LEFT_MOUSE_BUTTON) && associated.Box.Contains({input.GetMouseX() + Camera::pos.x, input.GetMouseY() + Camera::pos.y}))
	{
		Damage(std::rand() % 10 + 10);
	}
}

void Face::Render()
{
}

bool Face::Is(const std::string& type)
{
	return type == "face";
}


