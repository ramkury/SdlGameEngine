#include "Face.h"
#include "Sound.h"

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
}

void Face::Render()
{
}

bool Face::Is(const std::string& type)
{
	return type == "face";
}


