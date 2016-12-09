#pragma once
#include<SDL\SDL.h>

namespace DARE_Engine
{
	class FpsLimiter
	{
	public:

		FpsLimiter();

		void init(float FPSTarget);
		void beginFrame();

		void setFPSTarget(float FPSTarget);

		float end();

	private:

		float _FPSTarget;
		unsigned int _startTicks;

		void calculateFPS();

		float _fps, _frameTime, _maxFPS;


	};
}