#include <stdexcept>
#include "Sprite.h"
#include "SDL2/SDL_image.h"
#include "Game.h"

Sprite::Sprite()
{
	texture = nullptr;
}

Sprite::Sprite(std::string file)
{
	texture = nullptr;
	Open(file);
}


Sprite::~Sprite()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
	}
}

void Sprite::Open(std::string file)
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
	
	texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

	if (texture == nullptr)
	{
		throw std::runtime_error("Could not load texture " + file + ". Error: " + SDL_GetError());
	}

	int error = SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	if (error)
	{
		throw std::runtime_error("Could not query texture " + file);
	}

	SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h)
{
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Render(int x, int y)
{
	SDL_Rect dstRect;
	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = width;
	dstRect.h = height;
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);

}

int Sprite::GetWidth()
{
	return width;
}

int Sprite::GetHeight()
{
	return height;
}

bool Sprite::IsOpen()
{
	return texture != nullptr;
}
