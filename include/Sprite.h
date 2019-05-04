#pragma once
#include <string>
#include "SDL2/SDL.h"
#include "Component.h"

class Sprite : public Component
{
public:
	Sprite(GameObject& associated);
	Sprite(GameObject& associated, std::string file);
	~Sprite();
	void Open(std::string file);
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
	
private:
	SDL_Texture* texture;
	int width;
	int height;
	SDL_Rect clipRect;
	Vec2 scale = { 1, 1 };
};

