#include "Camera2D.h"

namespace Bengine
{
	Camera2D::Camera2D() :
		_position(0.0f, 0.0f),
		_cameraMatrix(1.0f),
		_orthoMatrix(1.0f),
		_scale(1.0f),
		_needsMatrixUpdate(true),
		_windowWidth(500),
		_windowHeight(500),
		MoveSpeed(3.0f),
		ScaleSpeed(0.1f)
	{

	}

	Camera2D::~Camera2D()
	{

	}

	const Camera2D& Camera2D::setPosition(const glm::vec2& newPosition)
	{
		_position = newPosition;
		_needsMatrixUpdate = true;
		return *this;
	}
	const Camera2D& Camera2D::setScale(float newScale)
	{
		_scale = newScale;
		_needsMatrixUpdate = true;
		return *this;
	}

	void Camera2D::init(int windowWidth, int windowHeight)
	{
		_windowWidth = windowWidth;
		_windowHeight = windowHeight;
		_orthoMatrix = glm::ortho(0.0f, (float)_windowWidth, 0.0f, (float)_windowHeight);
	}

	void Camera2D::update()
	{
		if (_needsMatrixUpdate)
		{
			//Camera Translation
			glm::vec3 translate(-_position.x + _windowWidth / 2, -_position.y + _windowHeight / 2, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);
			
			//Camera Scale
			glm::vec3 scale(_scale, _scale, 0.0f);
			//This makes the focus which the left-bottom of the texture will not a certain point.
			_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;
			//_cameraMatrix = glm::scale(_cameraMatrix, scale);
			_needsMatrixUpdate = false;
		}
	}

	glm::vec2 Camera2D::convertWindowToWorld(glm::vec2 windowCoords)
	{
		//Invert y direction
		windowCoords.y = _windowHeight - windowCoords.y;
		//Make it so that 0 is the center.
		windowCoords -= glm::vec2(_windowWidth / 2, _windowHeight / 2);
		//Scale the coordinates.
		windowCoords /= _scale;
		//Translate with the camera position.
		windowCoords += _position;

		return windowCoords;
	}
}