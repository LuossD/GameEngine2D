#include "Timing.h"

namespace Bengine
{
	FPSLimiter::FPSLimiter() : 
		_fps(0.0f), 
		_frameTime(0.0f),
		_maxFPS(60.0f), 
		_startTicks(0)
	{

	}

	FPSLimiter::~FPSLimiter()
	{

	}

	void FPSLimiter::init(float maxFPS)
	{
		setMaxFPS(maxFPS);
	}

	void FPSLimiter::setMaxFPS(float maxFPS)
	{
		_maxFPS = maxFPS;
	}

	void FPSLimiter::begin()
	{
		_startTicks = SDL_GetTicks();
	}

	float FPSLimiter::end()
	{
		calculateFPS();

		float frameTicks = SDL_GetTicks() - _startTicks;
		const float minFrameTime = 1000.f / _maxFPS;
		//Limit the FPS to the max FPS.
		if (minFrameTime > frameTicks)
		{
			SDL_Delay(minFrameTime - frameTicks);
		}

		return _fps;
	}

	void FPSLimiter::calculateFPS()
	{
		static const int NUM_SAMPLERS = 10;
		static float frameTimes[NUM_SAMPLERS];
		static int currentFrame = 0;

		static float prevTicks = SDL_GetTicks();
		float currentTicks;
		currentTicks = SDL_GetTicks();
		_frameTime = currentTicks - prevTicks;
		frameTimes[currentFrame % NUM_SAMPLERS] = _frameTime;

		prevTicks = currentTicks;

		int count;
		//It has to be here, otherwise count is going to be 0 the first time
		currentFrame++;
		if (currentFrame < NUM_SAMPLERS)
		{
			count = currentFrame;
		}
		else
		{
			count = NUM_SAMPLERS;
		}

		float frameTimeAverage = 0;
		for (int i = 0; i < count; ++i)
		{
			frameTimeAverage += frameTimes[i];
		}
		frameTimeAverage /= count;

		if (frameTimeAverage > 0)
		{
			_fps = 1000.0f / frameTimeAverage;
		}
		else
		{
			_fps = _maxFPS;
		}
	}
}