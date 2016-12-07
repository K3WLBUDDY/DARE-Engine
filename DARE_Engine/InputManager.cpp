#include "InputManager.h"

using namespace DARE_Engine;


void InputManager::pressKey(unsigned int keyID)
{
	_keyMap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID)
{
	_keyMap[keyID] = false;
}

bool InputManager::isKeyPressed(unsigned int keyID)
{
	//return _keyMap[keyID]; Associative Array - Creates a default variable here. Not Advised as it may assuem values for the varaible.

	auto it = _keyMap.find(keyID);
	if (it != _keyMap.end())
		return it->second;
	else
		false;
}



InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}
