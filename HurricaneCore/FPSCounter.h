//*******************************//
//
// Name:			FPSCounter.h
// Description:		Calculate the current frames per second of the game.
//					Only the class Game can access these functions.
//
// Author:			Edwin Chen
// Created:			Nov 11, 2016
// Last updated:	May 02, 2017
//
//*******************************//


#ifndef _FPS_COUNTER_H
#define _FPS_COUNTER_H

#include "Macro.h"

#define FPS_COUNTER FPSCounter::GetFPSCounter()

class FPSCounter {
	friend class Game;
	friend class DXApp;
protected:
	void CalculateFPS();

	FPSCounter() {}
	~FPSCounter() {}

	static FPSCounter* GetFPSCounter();

	void Init(float maxfps);
	void SetMaxFPS(float maxfps);

	void BeginFrame();
	float End(); // will compute FPS

protected:
	static UNIQUE_PTR(FPSCounter) _fpsInstance;
	friend DEFAULT_DELETE(FPSCounter);

	float _maxFPS;
	int   _startTicks;

	float _fps;
	float _frameTime;
};

#endif