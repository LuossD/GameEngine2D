#include "Window.h"
#include "Errors.h"

namespace Bengine
{
	Window::Window()
	{

	}
	Window::~Window()
	{

	}

	int Window::create(std::string windowName, int windowWidth, int windowHeight, unsigned int currentFlag)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;

		if (currentFlag & INVISIBLE)
		{
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlag & FULLSCREEN)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlag & BORDERLESS)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}
		_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);
		if (_sdlWindow == nullptr)
		{
			fatalError("SDL Window could not be created!");
		}
		/*if (window_mode & SDL_WINDOW_FULLSCREEN)
		{
			SDL_SetWindowSize(_window, 512, 384);
		}*/

		//set up GL context and give it to the window so we don't need to store it 
		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
		if (glContext == nullptr)
		{
			fatalError("SDL_GL Context could not be created!");
		}

		int errorLoad = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
		if (errorLoad == 0)
		{
			fatalError("Failed to initialize GLAD");
		}


		//Check the OpenGL Version.
		//This is going to be set to your current version of OpenGL on whatever computer.
		std::printf("*** OpenGL Version: %s ***\n", glGetString(GL_VERSION));

		//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		//设置窗口的清屏颜色---设置
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

		//Turn on vsync
		SDL_GL_SetSwapInterval(0);

		//Enable alpha blend
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::swapBuffer()
	{
		SDL_GL_SwapWindow(_sdlWindow);
	}
}