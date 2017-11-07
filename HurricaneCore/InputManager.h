//*******************************//
//
// Name:			InputManager.h
// Description:		Defines handlers for several types of input devices.
//					i.e. keyboard, mouse, gamepad, etc.
//
// Author:			Edwin Chen
// Special Thanks:  
//
// Created:			Jul 17, 2016
// Last updated:	Nov 06, 2017
//
//*******************************//


#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H

#include "Macro.h"
#include "HMath.h"

#define INPUT InputManager::GetInputManager()

namespace HurricaneEngine 
{
	class IHGame;

	class InputManager {
		friend class IHGame;
	protected:
		MAP(unsigned int, bool) _keyMap;

		static UNIQUE_PTR(InputManager) _inputManager;
		friend DEFAULT_DELETE(InputManager);

		HMath::VEC2 _oldMousePos;
		HMath::VEC2 _curMousePos;

	protected:
		InputManager();

		bool InitInput();
		void SetMousePos(unsigned int _x, unsigned int _y);
	public:
		~InputManager();

		static InputManager* GetInputManager();



		void KeyDown(unsigned int _key);
		void KeyUp(unsigned int _key);

		bool IsKeyDown(unsigned int _key);

		const HMath::VEC2& GetMousePos() const;

	};

} // end namespace HurricaneEngine

#endif