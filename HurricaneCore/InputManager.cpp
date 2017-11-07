#include "InputManager.h"
#include "Debugger.h"

using namespace HMath;
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
	for (unsigned int i = 0; i < 256; i++) 
	{
		_keyMap.insert(PAIR(unsigned int, bool)(i, false));
	}

	_curMousePos = VEC2(0.0f, 0.0f);
	_oldMousePos = _curMousePos;

	return true;
}


void InputManager::SetMousePos(unsigned int _x, unsigned int _y) 
{
	_curMousePos = VEC2(_x, _y);
	_oldMousePos = _curMousePos;
}



void InputManager::KeyDown(unsigned int _key)
{
	// If a key is pressed then save that state in the key array
	_keyMap[_key] = true;
	return;
}

void InputManager::KeyUp(unsigned int _key)
{
	// If a key is released then clear that state in the key array
	_keyMap[_key] = false;
	return;
}

bool InputManager::IsKeyDown(unsigned int _key)
{
	// Return what state the key is in (pressed/not pressed)
	return _keyMap[_key];
}

const VEC2& HurricaneEngine::InputManager::GetMousePos() const
{
	return _curMousePos;
}
