#include <stdexcept>
#include "Music.h"

Music::Music() : music(nullptr)
{
}

Music::Music(std::string file) : Music()
{
	Open(file);
}

void Music::Play(int times)
{
	Mix_PlayMusic(music, times);
}

void Music::Stop(int msToStop)
{
	Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file)
{
	music = Mix_LoadMUS(file.c_str());
	if (!IsOpen())
	{
		throw std::runtime_error("Could not open music file: " + file + ". Error: " + Mix_GetError());
	}
}

bool Music::IsOpen()
{
	return music != nullptr;
}


Music::~Music()
{
	if (IsOpen())
	{
		Stop(0);
		Mix_FreeMusic(music);
	}
}
