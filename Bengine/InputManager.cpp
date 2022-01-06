#include "InputManager.h"

namespace Bengine
{
	InputManager::InputManager() : _mouseCoords(0.0f)
	{

	}

	InputManager::~InputManager()
	{

	}

	void InputManager::pressKey(size_t keyID)
	{
		//It's going to first check if this keyID is even in the map,
		//if it's not in the map, it's going to go ahead and create it.
		_keyMap[keyID] = true;
	}

	void InputManager::releaseKey(size_t keyID)
	{
		_keyMap[keyID] = false;
	}

	bool InputManager::isKeyPressed(size_t keyID)
	{
		/*
		If nobody has ever pressed or released keyID, then this isn't going 
		 to exist in the map yet, and whenever we call this _keyMap[keyID]
		 right here, this is what's called treating it as an associative array
		 by the way. What is going to do is it's going to create a default variable therefore
		 , it's going to create a value for the keyID and then a random value, it could be 
		 true or false, we're not going to know which one it is. So we don't want to do it this way.
		*/
		//return _keyMap[keyID];

		auto it = _keyMap.find(keyID);
		if (it != _keyMap.end())
		{
			return it->second;
		}
		else
		{
			return false;
		}
	}

	void  InputManager::setMouseCoords(float x, float y)
	{
		_mouseCoords.x = x;
		_mouseCoords.y = y;
	}

	const glm::vec2& InputManager::getMouseCoords() const
	{
		return _mouseCoords;
	}
}
