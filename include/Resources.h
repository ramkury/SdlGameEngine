#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "Music.h"
#include <unordered_map>

class Resources
{
public:
	static SDL_Texture* GetImage(const std::string& file);
	static void ClearImages();

	static Mix_Music* GetMusic(const std::string& file);
	static void ClearMusic();

	static Mix_Chunk* GetSound(const std::string& file);
	static void ClearSound();

private:
	static std::unordered_map<std::string, SDL_Texture*> imageTable;
	static std::unordered_map<std::string, Mix_Music*> musicTable;
	static std::unordered_map<std::string, Mix_Chunk*> soundTable;
};

