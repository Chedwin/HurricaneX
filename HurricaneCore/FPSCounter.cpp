#include "FPSCounter.h"

UNIQUE_PTR(FPSCounter) FPSCounter::_fpsInstance(nullptr); // Declare static unique pointer


FPSCounter* FPSCounter::GetFPSCounter()
{
	if (_fpsInstance.get() == nullptr) 
		_fpsInstance.reset(new FPSCounter());
	
	return _fpsInstance.get();
}


FPSCounter::FPSCounter() : _fps(0.0f), _frameCount(0), _maxFPS(1000.0f)
{
	// empty
}

FPSCounter::~FPSCounter()
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FPSCounter::SetMaxFPS(float maxfps)
{
	_maxFPS = maxfps;
}


void FPSCounter::UpdateFPS() 
{
	_frameCount++;

	if (_interval.value() > 1000 /* milliseconds*/) 
	{
		// save the current counter value to m_fps
		_fps = _frameCount;

		// reset the counter and the interval
		_frameCount = 0;
		_interval.Reset();
	}

	if (1000.0f / _maxFPS > _frameCount) 
	{
		Sleep(1000.0f / _maxFPS - _frameCount);	 // equivalent to SDL_Delay	
	}		
}
