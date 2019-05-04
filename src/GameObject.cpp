#include "GameObject.h"
#include "Sound.h"

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
	components.clear();
}

void GameObject::Start()
{
	if (started)
	{
		return;
	}

	for (auto& c : components)
	{
		c->Start();
	}

	started = true;
}

void GameObject::Update(float dt)
{
	for (size_t i = 0; i < components.size(); ++i)
	{
		components[i]->Update(dt);
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
	return isDead;
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

void GameObject::NotifyCollision(GameObject& other)
{
	for (size_t i = 0; i < components.size(); ++i)
	{
		components[i]->NotifyCollision(other);
	}
}

std::shared_ptr<Component> GameObject::GetComponent(const std::string& type)
{
	for (auto& c : components)
	{
		if (c->Is(type))
		{
			return c;
		}
	}
	return nullptr;
}
