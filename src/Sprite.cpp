#include <stdexcept>
#include "Sprite.h"
#include "SDL2/SDL_image.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

Sprite::Sprite(GameObject& associated) : Component(associated), texture(nullptr)
{
}

Sprite::Sprite(GameObject& associated, std::string file) : Sprite(associated)
{
	Open(file);
}


Sprite::~Sprite()
{
}

void Sprite::Open(std::string file)
{	
	texture = Resources::GetImage(file);

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
	clipRect = { x, y, w, h };
}

void Sprite::Render()
{
	Render(int(associated.Box.x - Camera::pos.x), int(associated.Box.y - Camera::pos.y));
}

void Sprite::Render(int x, int y) const
{
	SDL_Rect dstRect = { x, y, clipRect.w, clipRect.h };
	SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
}

int Sprite::GetWidth() const
{
	return width;
}

int Sprite::GetHeight() const
{
	return height;
}

bool Sprite::IsOpen() const
{
	return texture != nullptr;
}

void Sprite::Update(float dt)
{
}

bool Sprite::Is(const std::string& type)
{
	return type == "Sprite";
}
