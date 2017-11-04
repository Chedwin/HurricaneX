//*******************************//
//
// Name:			FPSCounter.h
// Description:		Calculate the current frames per second of the game.
//					Only the class Game can access these functions.
//
// Author:			Edwin Chen
// Created:			Nov 11, 2016
// Last updated:	Nov 04, 2017
//
//*******************************//


#ifndef _FPS_COUNTER_H
#define _FPS_COUNTER_H

#include "Macro.h"

#define MAX_FRAME_RATE 120.0f

namespace HurricaneEngine 
{
	//class IHGame;

	class FPSCounter {
		//friend class IHGame;
	protected:
		static UNIQUE_PTR(FPSCounter) _instance;
		friend DEFAULT_DELETE(FPSCounter);

		const float _maxFPS = MAX_FRAME_RATE;
		
		int m_fps, m_count;
		unsigned long m_startTime;

	protected:
		FPSCounter() {}
	public:
		~FPSCounter() {}

		static FPSCounter* GetFPSCounter();

		void Initialize();
		void Frame();
		int  GetFps();
	};

} // end namespace HurricaneEngine


#endif