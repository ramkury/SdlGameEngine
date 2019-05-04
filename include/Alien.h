#pragma once
#include "Component.h"
#include <queue>

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
private:
	class Action
	{
	public:
		enum class ActionType
		{
			MOVE,
			SHOOT
		};

		Action(ActionType type, float x, float y) : type(type), pos(x, y) {};
		ActionType type;
		Vec2 pos;
	};

	Vec2 speed;
	int hp = 30;

	std::queue<Action> taskQueue;
	std::vector<std::weak_ptr<GameObject>> minionArray;
};

