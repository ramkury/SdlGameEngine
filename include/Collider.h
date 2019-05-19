#pragma once
#include "Component.h"

class Collider : public Component
{
public:
	Collider(GameObject& associated, Vec2 scale = {1, 1}, Vec2 offset = {0,0});
	Rect Box;

	void Update(float dt) override;
	void Render() override;
	bool Is(const std::string& type) override;

	void SetScale(Vec2 scale);
	void SetOffset(Vec2 offset);

private:
	Vec2 scale;
	Vec2 offset;
};

