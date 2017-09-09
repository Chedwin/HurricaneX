//*******************************//
//
// Name:			GameTimer.h
// Description:		
//					
//
// Author:			Frank Luna 
// Special Thanks:  
//
// Created:			2011
// Last updated:	May 09, 2017
//
//*******************************//

#ifndef _GAME_TIMER_H
#define _GAME_TIMER_H

#include "Macro.h"

class GameTimer {
public:
	GameTimer();
	~GameTimer() {}

	float TotalTime() const;  // in seconds
	float DeltaTime() const; // in seconds

	void Reset(); // Call before message loop.
	void Start(); // Call when unpaused.
	void Stop();  // Call when paused.
	void Tick();  // Call every frame.

private:
	double mSecondsPerCount;
	double mDeltaTime;

	__int64 mBaseTime;
	__int64 mPausedTime;
	__int64 mStopTime;
	__int64 mPrevTime;
	__int64 mCurrTime;

	bool mStopped;
};

#endif