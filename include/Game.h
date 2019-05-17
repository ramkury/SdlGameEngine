#pragma once
#include <string>
#include "SDL2/SDL.h"
#include "State.h"

class Game
{
public:
	Game(const Game&) = delete;
	~Game();
	void Run();
	SDL_Renderer* GetRenderer() const;
	static Game& GetInstance();
	State* GetState() const;
	float GetDeltaTime() const;
private:
	Game(std::string title, int width, int height);
	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* state;
	unsigned frameStart = 0;
	float dt = 0.f;
	void CalculateDeltaTime();
};

