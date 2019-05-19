#pragma once
#include "Component.h"
#include <queue>
#include "Timer.h"

class Alien : public Component
{
public:
	Alien(GameObject& associated, int nMinions);
	~Alien();

	void Start() override;
	void Update(float dt) override;
	void Render() override;
	bool Is(const std::string& type) override;
	void NotifyCollision(GameObject& other) override;
	
	static int alienCount;
private:
	enum AlienState
	{
		MOVING,
		RESTING
	};
	AlienState state = RESTING;
	Timer restTimer;
	Vec2 destination;
	Vec2 speed;
	int hp = 30;
	std::vector<std::weak_ptr<GameObject>> minionArray;
	void Shoot(Vec2 target);
	void Die();
};

