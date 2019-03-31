#pragma once
#include <string>
#include "SDL2/SDL.h"
#include "State.h"

class Game
{
private:
	Game(std::string title, int width, int height);
	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* state;
public:
	~Game();
	void Run();
	SDL_Renderer* GetRenderer();
	static Game& GetInstance();
	State& GetState();
};

