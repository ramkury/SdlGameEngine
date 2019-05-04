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
	void Start();
	bool QuitRequested();
	void LoadAssets();
	void Update(float dt);
	void Render();
	std::weak_ptr<GameObject> AddObject(GameObject* go);
	std::weak_ptr<GameObject> GetObjectPointer(GameObject* go);


private:
	Music music;
	bool quitRequested = false;
	bool started = false;
	std::vector<std::shared_ptr<GameObject>> objectArray;
};

