#include "InputManager.h"

using namespace HurricaneEngine;

UNIQUE_PTR(InputManager) InputManager::_inputManager(nullptr);

InputManager* InputManager::GetInputManager()
{
	if (_inputManager.get() == nullptr)
	{
		/// I originally set the uniqu_evntptr to be null in the constructor - reset() sets the new address
		_inputManager.reset(new InputManager());
	}
	return _inputManager.get();
}

////////////////////////////////////////////////////////////////////////////////////////////////

InputManager::InputManager()
{
	InitInput();
}


InputManager::~InputManager()
{
	// empty
}

////////////////////////////////////////////////////////////////////////////////////////////////

bool InputManager::InitInput()
{
	// Initialize all the keys to being released and not pressed
	for (int i = 0; i < 256; i++)
		_keys[i] = false;

	return true;
}

void InputManager::KeyDown(unsigned int input)
{
	// If a key is pressed then save that state in the key array
	_keys[input] = true;
	return;
}

void InputManager::KeyUp(unsigned int input)
{
	// If a key is released then clear that state in the key array
	_keys[input] = false;
	return;
}

bool InputManager::IsKeyDown(unsigned int key)
{
	// Return what state the key is in (pressed/not pressed)
	return _keys[key];
}