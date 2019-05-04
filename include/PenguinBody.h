#pragma once
#include "Component.h"
class PenguinBody : public Component
{
public:
	PenguinBody(GameObject& associated);
	~PenguinBody();

	void Start() override;
	void Update(float dt) override;
	void Render() override;
	bool Is(const std::string& type) override;

	static PenguinBody* player;

private:
	std::weak_ptr<GameObject> pcannon;
	Vec2 speed;
	float linearSpeed = 0;
	float angle = 0;
	int hp = 30;
};

