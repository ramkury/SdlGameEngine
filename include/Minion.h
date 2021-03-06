#pragma once
#include "Component.h"
class Minion : public Component
{
public:
	Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
	void Update(float dt) override;
	void Render() override;
	bool Is(const std::string& type) override;
	void NotifyCollision(GameObject& other) override;
	void Shoot(Vec2 target) const;
private:
	std::weak_ptr<GameObject> alienCenter;
	float arc;
};

