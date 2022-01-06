#pragma once
#include <SDL/SDL.h>

namespace Bengine
{
	class FPSLimiter
	{
	public:
		FPSLimiter();
		~FPSLimiter();

		void init(float targetFPS);

		void setMaxFPS(float maxFPS);

		void begin();

		//end will return the current FPS.
		float end();

	private:
		void calculateFPS();

		float _fps;
		float _frameTime;
		float _maxFPS;
		Uint32 _startTicks;
	};
}