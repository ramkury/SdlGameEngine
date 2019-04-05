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
			dynamic_cast<Sound*>(sound)->Play(1);
		}
	}
}

void Face::Update(float dt)
{
}

void Face::Render()
{
}

bool Face::Is(std::string type)
{
	return type == "face";
}


