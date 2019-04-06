#include <stdexcept>
#include "Sprite.h"
#include "SDL2/SDL_image.h"
#include "Game.h"

Sprite::Sprite(GameObject& associated) : Component(associated), texture(nullptr)
{
}

Sprite::Sprite(GameObject& associated, std::string file) : Sprite(associated)
{
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
	associated.Box.w = float(width);
	associated.Box.h = float(height);
}

void Sprite::SetClip(int x, int y, int w, int h)
{
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Render()
{
	SDL_Rect dstRect;
	dstRect.x = int(associated.Box.x);
	dstRect.y = int(associated.Box.y);
	dstRect.w = int(associated.Box.w);
	dstRect.h = int(associated.Box.h);
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

void Sprite::Update(float dt)
{
}

bool Sprite::Is(const std::string& type)
{
	return type == "sprite";
}
