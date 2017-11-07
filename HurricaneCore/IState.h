//*******************************//
//
// Name:			IState.h
// Description:		Template Interface to be used by the Finite State Machine or State Stack.
//					These states could be used for a varitey of uses such as: 
//						Scenes, Screens, AI, RPG Combat systems, etc.
//					
//
// Author:			Edwin Chen
// Special Thanks:  Dan Schuller 
//						(https://gamedevelopment.tutsplus.com/articles/how-to-build-a-jrpg-a-primer-for-game-developers--gamedev-6676#birthplace)
//
// Created:			Oct 21, 2017
// Last updated:	Nov 06, 2017
//
//*******************************//

#ifndef _ISTATE_H
#define _ISTATE_H

#include "Macro.h"

namespace HurricaneEngine
{
	template <typename T>
	class IState {
	protected:
		STRING _stateName;

	public:
		IState<T>(const STRING& _name = "") : _stateName(_name) {}
		virtual ~IState<T>() {}

		virtual void EnterState(T* owner)						= 0;
		virtual void ExitState(T* owner)						= 0;
		virtual void UpdateState(T* owner, const float _dt)		= 0;
		virtual void RenderState(T* owner)						= 0;


		STRING StateName() const 
		{
			return _stateName;
		}
	};

} // end namespace HurricaneEngine

#endif