#include "Resources.h"
#include <SDL2/SDL_image.h>
#include "Game.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(const std::string& file)
{
	const auto iterator = imageTable.find(file);
	if (iterator != imageTable.end()) // Texture is already loaded
	{
		return iterator->second;
	}

	// Texture hasn't been loaded yet.
	const auto texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

	if (texture == nullptr)
	{
		throw std::runtime_error("Could not load texture " + file + ". Error: " + SDL_GetError());
	}

	imageTable[file] = texture;
	//imageTable.emplace(file, texture);

	return texture;
}

void Resources::ClearImages()
{
	for (auto& texture : imageTable)
	{
		SDL_DestroyTexture(texture.second);
	}
	imageTable.clear();
}

Mix_Music* Resources::GetMusic(const std::string& file)
{
	const auto iterator = musicTable.find(file);
	if (iterator != musicTable.end())
	{
		return iterator->second;
	}

	const auto music = Mix_LoadMUS(file.c_str());
	if (music == nullptr)
	{
		throw std::runtime_error("Could not open music file: " + file + ". Error: " + Mix_GetError());
	}

	musicTable.emplace(file, music);

	return music;
}

void Resources::ClearMusic()
{
	for (auto& music : musicTable)
	{
		Mix_FreeMusic(music.second);
	}
	musicTable.clear();
}

Mix_Chunk* Resources::GetSound(const std::string& file)
{
	const auto iterator = soundTable.find(file);
	if (iterator != soundTable.end())
	{
		return iterator->second;
	}

	const auto chunk = Mix_LoadWAV(file.c_str());
	if (chunk == nullptr)
	{
		throw std::runtime_error("Could not open sound file: " + file + ". Error: " + Mix_GetError());
	}

	soundTable.emplace(file, chunk);
	
	return chunk;
}

void Resources::ClearSound()
{
	for (auto& chunk : soundTable)
	{
		Mix_FreeChunk(chunk.second);
	}
	soundTable.clear();
}
