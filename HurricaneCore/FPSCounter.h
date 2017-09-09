//*******************************//
//
// Name:			FPSCounter.h
// Description:		Calculate the current frames per second of the game.
//					Only the class Game can access these functions.
//
// Author:			Edwin Chen
// Created:			Nov 11, 2016
// Last updated:	May 08, 2017
//
//*******************************//


#ifndef _FPS_COUNTER_H
#define _FPS_COUNTER_H

#include "Macro.h"

class Interval {
	friend class FPSCounter;
protected:
	// Ctor
	inline Interval() : _initialTick(GetTickCount())
	{
	}

	// Dtor
	virtual ~Interval()
	{
	}

	inline unsigned int value() const
	{
		return GetTickCount() - _initialTick;
	}

	inline void Reset() 
	{
		_initialTick = GetTickCount();
	}

private:
	unsigned int _initialTick;
};


///////////////////////////////////////////////////////////////////////////////////

#define FPS_COUNTER FPSCounter::GetFPSCounter()	

class FPSCounter {
	friend class Game;
	friend class DXApp;
protected:
	FPSCounter();
public:
	~FPSCounter();
	static FPSCounter* GetFPSCounter();

	void SetMaxFPS(float maxfps);

	void UpdateFPS();

	inline float GetFPS() const {
		return _fps;
	}

protected:
	static UNIQUE_PTR(FPSCounter) _fpsInstance;
	friend DEFAULT_DELETE(FPSCounter);

	float _maxFPS = 1000.0f;
	int   _startTicks;

	float _fps;
	float _frameCount;

	Interval _interval;
};


#endif