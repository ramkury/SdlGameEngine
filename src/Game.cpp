#include "Game.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Resources.h"
#include "InputManager.h"

Game* Game::instance = nullptr;

Game::Game(std::string title, int width, int height)
{
	// Singleton
	if (instance != nullptr)
	{
		throw std::logic_error("Trying to create more than one instances of a singleton (Game)");
	}
	instance = this;

	// Seeding random number generator
	srand(time(NULL));

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
	{
		throw std::runtime_error(std::string("SDL2/SDL_Init error. Code: ") + SDL_GetError());
	}

	int res = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	std::cout << "IMG_Init returned " << res << std::endl;

	res = Mix_Init(MIX_INIT_OGG);
	std::cout << "Mix_Init returned " << res << std::endl;

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	std::cout << "Mix_OpenAudio returned " << res << std::endl;

	Mix_AllocateChannels(32);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	state = new StageState();
}


void Game::CalculateDeltaTime()
{
	const auto currentFrame = SDL_GetTicks();
	dt = (currentFrame - frameStart) / 1000.f;
	frameStart = currentFrame;
}

Game::~Game()
{
	delete state;
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Game::Run()
{
	state->Start();

	while (!state->QuitRequested())
	{
		CalculateDeltaTime();
		InputManager::GetInstance().Update();
		state->Update(dt);
		state->Render();
		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}

	Resources::ClearImages();
	Resources::ClearMusic();
	Resources::ClearSound();
}

SDL_Renderer* Game::GetRenderer() const
{
	return renderer;
}

Game& Game::GetInstance()
{
	if (instance == nullptr)
	{
		new Game("Ricardo Kury - 14/0161082", 1024, 600);
	}
	return *instance;
}

StageState* Game::GetState() const
{
	return state;
}

float Game::GetDeltaTime() const
{
	return dt;
}
