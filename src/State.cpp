#include "State.h"
#include "SDL2/SDL.h"

State::State() :
	bg("assets/img/ocean.jpg"),
	quitRequested(false),
	music("assets/audio/stageState.ogg")
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
