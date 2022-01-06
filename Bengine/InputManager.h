#pragma once
#include <glm/glm.hpp>
#include <unordered_map>

namespace Bengine
{
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void pressKey(size_t keyID);
		void releaseKey(size_t keyID);
		bool isKeyPressed(size_t keyID);

		void setMouseCoords(float x, float y);
		const glm::vec2& getMouseCoords() const;

	private:
		std::unordered_map<size_t, bool> _keyMap;
		glm::vec2 _mouseCoords;
	};
}


