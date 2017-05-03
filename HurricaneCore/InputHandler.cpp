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


InputHandler::InputHandler()
{
}


InputHandler::~InputHandler()
{
}
