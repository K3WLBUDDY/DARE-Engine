#include"Timing.h"

using namespace DARE_Engine;

FpsLimiter::FpsLimiter()
{

}

void FpsLimiter::setFPSTarget(float FPSTarget)
{
	_FPSTarget = FPSTarget;
}

void FpsLimiter::init(float FPSTarget)
{
	setFPSTarget(FPSTarget);
}

void FpsLimiter::calculateFPS()
{
	static const int num_Samples = 10;//To Average the Frame times over 10 frames.Using static since values must be retained whenever the frame is drawm.
	static float frameTimes[num_Samples];
	static int currentFrame = 0;
	static float previousTicks = SDL_GetTicks();
	float currentTicks;

	currentTicks = SDL_GetTicks(); //Gets the current ms since SDL was initialized

	_frameTime = currentTicks - previousTicks;
	frameTimes[currentFrame%num_Samples] = _frameTime;//Implementing Circular Buffer.
	previousTicks = currentTicks;

	int count;
	currentFrame++;

	if (currentFrame < num_Samples)
		count = currentFrame;

	else
		count = num_Samples;

	float frameTimeAverage = 0;

	for (int i = 0; i < count; i++)
		frameTimeAverage += frameTimes[i];

	frameTimeAverage /= count;

	if (frameTimeAverage>0)
		_fps = 1000.0f / frameTimeAverage;
	else
		_fps = 60.0f;
}

void FpsLimiter::beginFrame()
{
	_startTicks = SDL_GetTicks();
}

float FpsLimiter::end()
{

	calculateFPS();

	float frameTick = SDL_GetTicks() - _startTicks;

	if (1000.0f / _FPSTarget > frameTick)
		SDL_Delay(1000.0f / _FPSTarget - frameTick);
	return _fps;
}