#pragma once
#include <SDL/SDL.h>
#include <glad/glad.h>
#include <string>

namespace Bengine
{
	enum WindowFlags
	{
		INVISIBLE = 0x1,
		FULLSCREEN = 0x3,
		BORDERLESS = 0x4
	};
	class Window
	{
	public:
		Window();
		~Window();
		int create(std::string windowName, int windowWidth, int windowHeight, unsigned int currentFlag);
		void swapBuffer();
	private:
		SDL_Window* _sdlWindow;
		int _windowWidth, _windowHeight;
	};
}
