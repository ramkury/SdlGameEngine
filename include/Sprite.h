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
	void Render();
	int GetWidth();
	int GetHeight();
	bool IsOpen();

	void Update(float dt) override;
	bool Is(std::string type) override;
	
private:
	SDL_Texture* texture;
	int width;
	int height;
	SDL_Rect clipRect;
};

