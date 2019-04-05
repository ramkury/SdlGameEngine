#include "GameObject.h"
#include "Sound.h"

GameObject::GameObject() : isDead(false)
{
}


GameObject::~GameObject()
{
	components.clear();
}

void GameObject::Update(float dt)
{
	for (auto& c : components)
	{
		c->Update(dt);
	}
}

void GameObject::Render()
{
	if (isDead)
	{
		return;
	}

	for (auto& c : components)
	{
		c->Render();
	}
}

bool GameObject::IsDead()
{
	return isDead && !(dynamic_cast<Sound*>(GetComponent("sound"))->IsPlaying());
}

void GameObject::RequestDelete()
{
	isDead = true;
	Box.h = Box.y = 0;
}

void GameObject::AddComponent(Component * cpt)
{
	components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component * cpt)
{
	for (auto iter = components.begin(); iter != components.end(); ++iter)
	{
		if (iter->get() == cpt)
		{
			components.erase(iter);
			break;
		}
	}
}

Component * GameObject::GetComponent(std::string type)
{
	for (auto& c : components)
	{
		if (c->Is(type))
		{
			return c.get();
		}
	}
	return nullptr;
}
