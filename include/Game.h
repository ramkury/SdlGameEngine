#pragma once
#include <string>
#include "SDL2/SDL.h"
#include "StageState.h"
#include "State.h"
#include <stack>

class Game
{
public:
	Game(const Game&) = delete;
	~Game();
	void Run();
	SDL_Renderer* GetRenderer() const;
	static Game& GetInstance();
	State& GetCurrentState() const;
	void Push(State* state);
	float GetDeltaTime() const;
private:
	Game(std::string title, int width, int height);
	static Game* instance;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	State* storedState = nullptr;
	std::stack<std::unique_ptr<State>> stateStack;
	unsigned frameStart = 0;
	float dt = 0.f;
	void CalculateDeltaTime();
};

