#include "State.h"

State::~State()
{
	objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject* object)
{
	objectArray.emplace_back(object);
	if (started)
	{
		object->Start();
	}
	return objectArray.back();
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* object)
{
	for (auto& ptr : objectArray)
	{
		if (ptr.get() == object)
		{
			return ptr;
		}
	}
	return std::weak_ptr<GameObject>();
}

bool State::PopRequested() const
{
	return popRequested;
}

bool State::QuitRequested() const
{
	return quitRequested;
}

void State::StartArray()
{
	if (started)
	{
		return;
	}
	for (auto && object : objectArray)
	{
		object->Start();
	}
	started = true;
}

void State::UpdateArray(float dt)
{
	for (int i = objectArray.size() - 1; i >= 0; i--)
	{
		objectArray[i]->Update(dt);
	}
	for (int i = objectArray.size() - 1; i >= 0; i--)
	{
		if (objectArray[i]->IsDead())
		{
			objectArray.erase(objectArray.begin() + i);
		}
	}
}

void State::RenderArray()
{
	for (auto&& object : objectArray)
	{
		object->Render();
	}
}
