//*******************************//
//
// Name:			FiniteStateMachine.h
// Description:		Template class that defines a standard FSM
//					Accepts variants of IState<T> template class to be used for universal purposes.
//					See IState.h 
//
//
// Author:			Edwin Chen
// Special Thanks:	
//
// Created:			Oct 21, 2017
// Last updated:	Nov 06, 2017
//
//*******************************//

#ifndef _FINITE_STATE_MACHINE_H
#define _FINITE_STATE_MACHINE_H

#include "Macro.h"
#include "IState.h"
#include "ResourceManager.h"

namespace HurricaneEngine
{

	template <typename T>
	class FiniteStateMachine {
	protected:
		ResourceManager<IState<T>> _stateManager;

		IState<T>* _currentState;
		T* _owner;

	public:
		FiniteStateMachine(T* _obj)
		{
			_owner = _obj;
			_currentState = nullptr;
		}

		~FiniteStateMachine()
		{
			Clear();
		}

		void Clear()
		{
			_stateManager.EmptyResourceMap();
		}


		void AddState(IState<T>* _state)
		{
			_stateManager.Add(_state->StateName(), _state);
		}

		void ChangeState(IState<T>* _state)
		{
			if (_currentState)
				_currentState->ExitState(_owner);

			_currentState = _state;
			_currentState->EnterState(_owner);
		}

		void UpdateState(const float _dt)
		{
			if (_currentState)
				_currentState->UpdateState(_owner, _dt);
		}

		void RenderState()
		{
			if (_currentState)
				_currentState->RenderState(_owner);
		}

		IState<T>* GetCurrentState() const 
		{
			return _currentState;
		}

		IState<T>* GetState(const STRING& _name) const 
		{
			return _stateManager.GetResource(_name);
		}

		IState<T>* GetState(unsigned int _index) const
		{
			return _stateManager.GetResource(_index);
		}

		// INLINE
		inline int Count() const 
		{
			return _stateManager.GetSize();
		}
		inline bool IsEmpty() const 
		{
			return _stateManager.IsEmpty();
		}
		

	};

} // end namespace HurricaneEngine

#endif




