#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Component.h"
#include "Rect.h"

#define GET_COMPONENT(GO, TYPE) std::static_pointer_cast<TYPE>(GO->GetComponent(#TYPE))

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
	double AngleDeg = 0;

private:
	std::vector<std::shared_ptr<Component>> components;
	bool isDead = false;
	bool started = false;
};

