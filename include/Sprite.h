#pragma once
#include <string>
#include "SDL2/SDL.h"
#include "Component.h"
#include "Timer.h"

class Sprite : public Component
{
public:
	Sprite(GameObject& associated);
	Sprite(GameObject& associated, const std::string& file, int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);
	~Sprite();
	void Open(const std::string& file);
	void SetClip(int x, int y, int w, int h);
	void Render() override;
	void Render(int x, int y, int w, int h) const;
	int GetWidth() const;
	int GetHeight() const;
	bool IsOpen() const;

	void Update(float dt) override;
	bool Is(const std::string& type) override;

	void SetScale(float scaleX, float scaleY);
	Vec2 GetScale() const;

	void SetFrame(int frame);
	void SetFrameCount(int frameCount);
	void SetFrameTime(float frameTime);
	
private:
	void clipFrame();

	SDL_Texture* texture;
	int width;
	int height;
	SDL_Rect clipRect;
	float secondsToSelfDestruct;
	Timer selfDestructCount;
	Vec2 scale = { 1, 1 };
	int frameCount = 0;
	int currentFrame = 0;
	float timeElapsed = 0;
	float frameTime = 0;
	int frameWidth = 0;
};

