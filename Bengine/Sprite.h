#pragma once
#include <glad/glad.h>
#include <string>
#include "GLTexture.h"

namespace Bengine
{
	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void initSprite(float x, float y, float width, float height, std::string texturePath);
		void draw();

	private:
		float _x;
		float _y;
		float _width;
		float _height;
		GLuint _vboID;
		GLTexture _texture;
	};
}
