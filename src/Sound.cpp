#include "Sound.h"
#include <stdexcept>

Sound::Sound(GameObject & associated) : Component(associated), chunk(nullptr)
{
}

Sound::Sound(GameObject & associated, std::string file) : Sound(associated)
{
	Open(file);
}

Sound::~Sound()
{
	if (IsOpen())
	{
		Mix_HaltChannel(channel);
		Mix_FreeChunk(chunk);
	}
}

void Sound::Play(int times)
{
	if (chunk != nullptr)
	{
		channel = Mix_PlayChannel(-1, chunk, times - 1);
	}
}

void Sound::Stop()
{
	if (chunk != nullptr)
	{
		Mix_HaltChannel(channel);
	}
}

void Sound::Open(std::string file)
{
	chunk = Mix_LoadWAV(file.c_str());
	if (!IsOpen())
	{
		throw std::runtime_error("Could not open sound file: " + file + ". Error: " + Mix_GetError());
	}
}

bool Sound::IsOpen()
{
	return chunk != nullptr;
}

void Sound::Update(float dt)
{
}

void Sound::Render()
{
}

bool Sound::Is(std::string type)
{
	return type == "sound";
}
