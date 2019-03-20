#pragma once
#include "Component.h"
#include "GameObject.h"

class Face : public Component
{
public:
	Face(GameObject& associated);
	
	void Damage(int damage);

	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual bool Is(std::string type) override;

private:
	int hitpoints;
};

