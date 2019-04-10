#include "Sound.h"
#include <stdexcept>
#include "Resources.h"

Sound::Sound(GameObject & associated) : Component(associated), chunk(nullptr)
{
}

Sound::Sound(GameObject & associated, std::string file) : Sound(associated)
{
	Open(file);
}

Sound::~Sound()
{
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
	if (IsOpen())
	{
		Mix_HaltChannel(channel);
	}
}

void Sound::Open(std::string file)
{
	chunk = Resources::GetSound(file);
}

bool Sound::IsOpen()
{
	return chunk != nullptr;
}

bool Sound::IsPlaying()
{
	return IsOpen() && Mix_Playing(channel);
}

void Sound::Update(float dt)
{
}

void Sound::Render()
{
}

bool Sound::Is(const std::string& type)
{
	return type == "sound";
}
