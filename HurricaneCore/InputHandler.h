//*******************************//
//
// Name:			InputHandler.h
// Description:		Defines handlers for several types of input devices.
//					i.e. keyboard, mouse, gamepad, etc.
//
// Author:			Edwin Chen
// Special Thanks:  
//
// Created:			Jul 17, 2016
// Last updated:	May 02, 2017
//
//*******************************//


#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "Macro.h"

#define INPUT InputHandler::GetInputHandler()

class InputHandler {
private:
	InputHandler();
public:
	~InputHandler();

	static InputHandler* GetInputHandler();

protected:
	static UNIQUE_PTR(InputHandler) _inputHandler;
	friend DEFAULT_DELETE(InputHandler);
};

#endif