#pragma once
#include "GameObject.h"

class Camera
{
public:
	static void Follow(GameObject* newFocus);
	static void Unfollow();
	static void Update(float dt);
	static Vec2 pos;
	static Vec2 speed;
	static GameObject* GetFocus();
private:
	static GameObject* focus;
};

