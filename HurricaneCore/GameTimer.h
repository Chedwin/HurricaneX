//*******************************//
//
// Name:			GameTimer.h
// Description:		Static game clock that calculates deltatime
//					
//
// Author:			Frank Luna
// Special Thanks:  
//
// Created:			2011
// Last updated:	Nov 04, 2017
//
//*******************************//

#ifndef _GAMETIMER_H
#define _GAMETIMER_H

namespace HurricaneEngine
{

	class GameTimer {
	public:
		GameTimer();

		float TotalTime() const;  // in seconds
		float DeltaTime() const;  // in seconds

		void Reset(); // Call before message loop.
		void Start(); // Call when unpaused.
		void Stop();  // Call when paused.
		void Tick();  // Call every frame.

	private:
		double _secondsPerCount;
		double _deltaTime;

		__int64 _baseTime;
		__int64 _pausedTime;
		__int64 _stopTime;
		__int64 _prevTime;
		__int64 _currTime;

		bool _stopped;
	};

}

#endif // _GAMETIMER_H