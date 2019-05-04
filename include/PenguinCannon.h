#pragma once
#include "Component.h"
class PenguinCannon : public Component
{
public:
	PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);

	void Update(float dt) override;
	void Render() override;
	bool Is(const std::string& type) override;
	void NotifyCollision(GameObject& other) override;

	void Shoot() const;
private:
	std::weak_ptr<GameObject> pbody;
	float angle = 0;
};

