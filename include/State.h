#pragma once
#include "Music.h"
#include "GameObject.h"
#include <vector>
#include <memory>

class State
{
public:
	State();
	~State();

	bool QuitRequested();
	void LoadAssets();
	void Update(float dt);
	void Render();
	void AddObject(int mouseX, int mouseY);

private:
	Music music;
	bool quitRequested = false;
	std::vector<std::shared_ptr<GameObject>> objectArray;
};

