#pragma once
#include <memory>
#include <GameObject.h>
class State
{
public:
	State() = default;
	virtual ~State();

	virtual void LoadAssets() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	virtual void Start() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual std::weak_ptr<GameObject> AddObject(GameObject* object);
	virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject* object);

	bool PopRequested() const;
	bool QuitRequested() const;

protected:
	void StartArray();
	virtual void UpdateArray(float dt);
	virtual void RenderArray();

	bool popRequested = false;
	bool quitRequested = false;
	bool started = false;

	std::vector<std::shared_ptr<GameObject>> objectArray;
	
};

