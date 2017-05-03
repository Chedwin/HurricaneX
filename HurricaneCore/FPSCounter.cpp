#include "FPSCounter.h"

UNIQUE_PTR(FPSCounter) FPSCounter::_fpsInstance(nullptr); // Declare static unique pointer


FPSCounter * FPSCounter::GetFPSCounter()
{
	if (_fpsInstance.get() == nullptr) 
		_fpsInstance.reset(new FPSCounter());
	
	return _fpsInstance.get();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FPSCounter::Init(float maxfps)
{
	SetMaxFPS(maxfps);
}

void FPSCounter::SetMaxFPS(float maxfps)
{
	_maxFPS = maxfps;
}

void FPSCounter::BeginFrame()
{
	_startTicks = GetTickCount();
}

float FPSCounter::End()
{
	CalculateFPS();

	float frameTicks = GetTickCount() - _startTicks;

	if (1000.0f / _maxFPS > frameTicks)
	{
		//SDL_Delay(1000.0f / _maxFPS - frameTicks);
	}

	return _fps;
}

void FPSCounter::CalculateFPS()
{
	// TODO
	static const int NUM_SAMPLES = 100;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float prevTicks = GetTickCount();
	float currTicks = GetTickCount();

	_frameTime = currTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	prevTicks = currTicks;

	int count;

	currentFrame++;
	if (currentFrame < NUM_SAMPLES)
	{
		count = currentFrame;
	}
	else
	{
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++)
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