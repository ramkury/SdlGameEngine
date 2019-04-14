#pragma once
#include "Component.h"
class CameraFollower : public Component
{
public:
	CameraFollower(GameObject& associated);
	void Update(float dt) override;
	void Render() override;
	bool Is(const std::string& type) override;
};

