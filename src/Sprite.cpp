#include <stdexcept>
#include "Sprite.h"
#include "SDL2/SDL_image.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

Sprite::Sprite(GameObject& associated) : Component(associated), texture(nullptr)
{
}

Sprite::Sprite(GameObject& associated, const std::string& file, int frameCount, float frameTime, float secondsToSelfDestruct) : Sprite(associated)
{
	this->secondsToSelfDestruct = secondsToSelfDestruct;
	Open(file);
	SetFrameCount(frameCount);
	SetFrameTime(frameTime);
	clipFrame();
}


Sprite::~Sprite()
{
}

void Sprite::Open(const std::string& file)
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
	Render(int(associated.Box.x - Camera::pos.x), int(associated.Box.y - Camera::pos.y), int(associated.Box.w), int(associated.Box.h));
}

void Sprite::Render(int x, int y, int w, int h) const
{
	SDL_Rect dstRect = { x, y, w, h };
	SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, associated.AngleDeg, nullptr, SDL_FLIP_NONE);
}

int Sprite::GetWidth() const
{
	return int(frameWidth * scale.x);
}

int Sprite::GetHeight() const
{
	return int(height * scale.y);
}

bool Sprite::IsOpen() const
{
	return texture != nullptr;
}

void Sprite::Update(float dt)
{
	if (secondsToSelfDestruct > 0)
	{
		selfDestructCount.Update(dt);
		if (selfDestructCount.Get() >= secondsToSelfDestruct)
		{
			associated.RequestDelete();
		}
	}

	timeElapsed += dt;
	if (timeElapsed >= frameTime)
	{
		timeElapsed -= frameTime;
		currentFrame = (currentFrame + 1) % frameCount;
		clipFrame();
	}
}

bool Sprite::Is(const std::string& type)
{
	return type == "Sprite";
}

void Sprite::SetScale(float scaleX, float scaleY)
{
	if (scaleX != 0)
	{
		scale.x = scaleX;
		const auto newWidth = width * scaleX;
		associated.Box.x += (associated.Box.w - newWidth) / 2;
		associated.Box.w = newWidth;
	}
	if (scaleY != 0)
	{
		scale.y = scaleY;
		const auto newHeight = height * scaleY;
		associated.Box.y += (associated.Box.y - newHeight) / 2;
		associated.Box.h = newHeight;
	}
}

Vec2 Sprite::GetScale() const
{
	return scale;
}

void Sprite::SetFrame(int frame)
{
	currentFrame = frame;
	clipFrame();
}

void Sprite::SetFrameCount(int frameCount)
{
	this->frameCount = frameCount;
	frameWidth = width / frameCount;
	associated.Box.w = GetWidth();
}

void Sprite::SetFrameTime(float frameTime)
{
	this->frameTime = frameTime;
}

void Sprite::clipFrame()
{
	SetClip(frameWidth * currentFrame, 0, frameWidth, height);
}
