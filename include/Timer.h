#pragma once
class Timer
{
public:
	Timer() = default;
	void Update(float dt);
	void Restart();
	float Get();

private:
	float time = 0;
};

