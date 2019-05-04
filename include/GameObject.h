#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Component.h"
#include "Rect.h"

class Component;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Start();
	void Update(float dt);
	void Render();
	bool IsDead();
	void RequestDelete();
	void AddComponent(Component* cpt);
	void RemoveComponent(Component* cpt);
	std::shared_ptr<Component> GetComponent(const std::string& type);

	Rect Box;

private:
	std::vector<std::shared_ptr<Component>> components;
	bool isDead = false;
	bool started = false;
};

