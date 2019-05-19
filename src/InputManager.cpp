#include "InputManager.h"
#include <SDL2/SDL.h>
#include "Camera.h"

void InputManager::Update()
{
	SDL_Event event;

	SDL_GetMouseState(&mouseX, &mouseY);
	quitRequested = false;
	updateCounter++;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (!event.key.repeat)
			{
				keyState[event.key.keysym.sym] = true;
				keyUpdate[event.key.keysym.sym] = updateCounter;
			}
			break;
		case SDL_KEYUP:
			if (!event.key.repeat)
			{
				keyState[event.key.keysym.sym] = false;
				keyUpdate[event.key.keysym.sym] = updateCounter;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouseState[event.button.button] = true;
			mouseUpdate[event.button.button] = updateCounter;
			break;
		case SDL_MOUSEBUTTONUP:
			mouseState[event.button.button] = false;
			mouseUpdate[event.button.button] = updateCounter;
			break;
		case SDL_QUIT:
			quitRequested = true;
			break;
		default:
			break;
		}
	}
}

bool InputManager::KeyPress(int key)
{
	return keyState[key] && keyUpdate[key] == updateCounter;
}

bool InputManager::KeyRelease(int key)
{
	return !keyState[key] && keyUpdate[key] == updateCounter;
}

bool InputManager::IsKeyDown(int key)
{
	return keyState[key];
}

bool InputManager::MousePress(int button)
{
	return mouseState[button] && mouseUpdate[button] == updateCounter;
}

bool InputManager::MouseRelease(int button)
{
	return !mouseState[button] && mouseUpdate[button] == updateCounter;
}

bool InputManager::IsMouseDown(int button)
{
	return mouseState[button];
}

int InputManager::GetMouseX()
{
	return mouseX;
}

int InputManager::GetMouseY()
{
	return mouseY;
}

int InputManager::GetMouseMapX() const
{
	return int(mouseX) + int(Camera::pos.x);
}

int InputManager::GetMouseMapY() const
{
	return mouseY + int(Camera::pos.y);
}

Vec2 InputManager::GetMouseMapPosition() const
{
	return Vec2(float(mouseX), float(mouseY)) + Camera::pos;
}

bool InputManager::QuitRequested()
{
	return quitRequested;
}

InputManager& InputManager::GetInstance()
{
	static InputManager manager;
	return manager;
}

