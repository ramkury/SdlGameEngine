#pragma once
#include <SDL2/SDL_mouse.h>

#define LEFT_ARROW_KEY    SDLK_LEFT
#define RIGHT_ARROW_KEY   SDLK_RIGHT
#define UP_ARROW_KEY      SDLK_UP
#define DOWN_ARROW_KEY    SDLK_DOWN
#define SPACE_KEY         SDLK_SPACE
#define ESCAPE_KEY        SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT 

class InputManager
{
public:
	void Update();
	bool KeyPress(int key);
	bool KeyRelease(int key);
	bool IsKeyDown(int key);

	bool MousePress(int button);
	bool MouseRelease(int button);
	bool IsMouseDown(int button);

	int GetMouseX();
	int GetMouseY();

	bool QuitRequested();

	static InputManager& GetInstance();

private:
	InputManager() = default;

	template<typename T> class keyMapper
	{
		T container[416] = { 0 };
	public:
		T& operator[](int key)
		{
			return container[key >= 0x40000000 ? key - 0x3FFFFF81 : key];
		}
	};

	keyMapper<bool> keyState;
	keyMapper<int> keyUpdate;

	bool mouseState[6] = { false };
	int mouseUpdate[6] = { 0 };

	bool quitRequested = false;
	int updateCounter = 0;

	int mouseX = 0;
	int mouseY = 0;
};
