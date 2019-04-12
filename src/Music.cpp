#include <stdexcept>
#include "Music.h"
#include "Resources.h"

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
	music = Resources::GetMusic(file);
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
