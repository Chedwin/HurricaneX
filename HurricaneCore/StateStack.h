//*******************************//
//
// Name:			StateStack.h
// Description:		
//					
//
// Author:			Edwin Chen
// Special Thanks:	
//
// Created:			Oct 21, 2017
// Last updated:	Nov 06, 2017
//
//*******************************//

#ifndef _STATE_STACK_H
#define _STATE_STACK_H

#include "Macro.h"
#include "IState.h"

namespace HurricaneEngine 
{

	template <typename T>
	class StateStack {
	protected:
		STACK(IState<T>*) _stack;
		T* _owner;
		IState<T>* _currentState = nullptr;

	public:
		StateStack(T* _obj) 
		{
			_owner = _obj;
		}
		
		~StateStack() 
		{
			Clear();
		}

		void Clear() 
		{
			if (IsEmpty())
				return;
			
			while (!IsEmpty())
				_stack.pop();
		}

		void PushState(IState<T>* _state) 
		{
			_stack.push(_state);
		}

		void PopState() 
		{
			if (Count() <= 1)
				return;

			_currentState->ExitState(_owner);
			_stack.pop();
			_currentState = PeekState();
			_currentState->EnterState(_owner);
		}

		IState<T>* PeekState() const
		{
			return _stack.peek();
		}

		void UpdateState(const float _deltaTime) 
		{
			if(_currentState)
				_currentState->UpdateState(_owner, _deltaTime);
		}

		void RenderState()
		{
			if (_currentState)
				_currentState->RenderState(_owner);
		}

		// INLINE
		inline int Count() const 
		{
			return _stack.size();
		}

		inline bool IsEmpty() const 
		{
			return _stack.empty();
		}
	};

} // end namespace HurricaneEngine

#endif