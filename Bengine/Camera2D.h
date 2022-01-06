#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Bengine
{
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int windowWidth, int windowHeight);

		void update();

		glm::vec2 convertWindowToWorld(glm::vec2 windowCoords);

		const Camera2D& setPosition(const glm::vec2& newPosition);
		
		const Camera2D& setScale(float newScale);

		float getMoveSpeed() const { return MoveSpeed; }
		float getScaleSpeed() const { return ScaleSpeed; }

		glm::vec2 getPosition() const { return _position; }
		float getScale() const { return _scale; }
		glm::mat4 getCameraMatrix() const  { return _cameraMatrix; }

	private:
		int _windowWidth, _windowHeight;
		bool _needsMatrixUpdate;
		float _scale;
		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;
		const float MoveSpeed;
		const float ScaleSpeed;
	};

}
