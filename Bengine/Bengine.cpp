// Bengine.cpp : 定义静态库的函数。
//
#include <SDL/SDL.h>
#include <glad/glad.h>
#include "Bengine.h"

namespace Bengine
{
	int init()
	{
		SDL_Init(SDL_INIT_EVERYTHING);

		//双缓冲开启---设置
		//It shouldn't be in the back,it sets the state for that window before it's created.
		//It was probably already set by default by SDL,so there is no error when it's in the back. 
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}
}