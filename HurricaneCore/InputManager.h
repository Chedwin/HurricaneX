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
// Last updated:	May 20, 2017
//
//*******************************//


#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "Macro.h"

#define INPUT InputManager::GetInputManager()

namespace HurricaneEngine 
{

	class InputManager {
	protected:
		bool _keys[256];
		static UNIQUE_PTR(InputManager) _inputManager;
		friend DEFAULT_DELETE(InputManager);

	private:
		InputManager();
	public:
		~InputManager();

		static InputManager* GetInputManager();


		bool InitInput();

		void KeyDown(unsigned int);
		void KeyUp(unsigned int);

		bool IsKeyDown(unsigned int);

	};

} // end namespace HurricaneEngine
#endif