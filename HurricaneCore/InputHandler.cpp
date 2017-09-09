#include "InputHandler.h"

UNIQUE_PTR(InputHandler) InputHandler::_inputHandler(nullptr);

InputHandler* InputHandler::GetInputHandler() 
{
	if (_inputHandler.get() == nullptr)
	{
		/// I originally set the uniqu_evntptr to be null in the constructor - reset() sets the new address
		_inputHandler.reset(new InputHandler());
	}
	return _inputHandler.get();
}

////////////////////////////////////////////////////////////////////////////////////////////////

InputHandler::InputHandler()
{
	InitInput();
}


InputHandler::~InputHandler()
{
	// empty
}

////////////////////////////////////////////////////////////////////////////////////////////////

void InputHandler::InitInput()
{
	int i;

	// Initialize all the keys to being released and not pressed
	for (i = 0; i < 256; i++)
	{
		_keys[i] = false;
	}

	return;
}

void InputHandler::KeyDown(unsigned int input)
{
	// If a key is pressed then save that state in the key array
	_keys[input] = true;
	return;
}

void InputHandler::KeyUp(unsigned int input)
{
	// If a key is released then clear that state in the key array
	_keys[input] = false;
	return;
}

bool InputHandler::IsKeyDown(unsigned int key)
{
	// Return what state the key is in (pressed/not pressed)
	return _keys[key];
}