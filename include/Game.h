#pragma once
#include <string>
#include "SDL2/SDL.h"
#include "StageState.h"

class Game
{
public:
	Game(const Game&) = delete;
	~Game();
	void Run();
	SDL_Renderer* GetRenderer() const;
	static Game& GetInstance();
	StageState* GetState() const;
	float GetDeltaTime() const;
private:
	Game(std::string title, int width, int height);
	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	StageState* state;
	unsigned frameStart = 0;
	float dt = 0.f;
	void CalculateDeltaTime();
};

