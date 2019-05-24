#pragma once
#include "Music.h"
#include "GameObject.h"
#include <vector>
#include <memory>
#include "State.h"

class StageState : public State
{
public:
	StageState();
	StageState(const StageState& other) = delete;
	~StageState();

	void LoadAssets() override;
	void Update(float dt) override;
	void Render() override;
	
	void Start() override;
	void Pause() override;
	void Resume() override;

private:
	Music backgroundMusic;
	bool started = false;
};

