#include "State.h"
#include "SDL.h"

State::State() :
	bg("resources/img/ocean.jpg"),
	quitRequested(false),
	music("resources/audio/stageState.ogg")
{
	music.Play();
}

bool State::QuitRequested()
{
	return quitRequested;
}

void State::LoadAssets()
{
}

void State::Update(float dt)
{
	 quitRequested = SDL_QuitRequested();
}

void State::Render()
{
	bg.Render(0, 0);
}
