//*******************************//
//
// Name:			HTime.h
// Description:		Static game clock that calculates deltatime
//					
//
// Author:			jparedes90
// Special Thanks:  
//
// Created:			Jul 09, 2016
// Last updated:	Nov 06, 2017
//
//*******************************//

#ifndef _HTIME_H
#define _HTIME_H

#include "Macro.h"

namespace HurricaneEngine 
{

	class HTime {
	public:
		static void Update();

		static float GetDeltaTime();
	private:
		static __int64 m_prevFrame;
		static __int64 m_currentFrame;
		static __int64 m_freq;
		static float m_deltaTime;
		static float MAX_REFRESH_TIME;
	};

}


#endif