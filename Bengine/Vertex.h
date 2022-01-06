#pragma once
#include <glad/glad.h>

namespace Bengine
{
	struct Position
	{
		float x;
		float y;

		void setPosition(float x, float y)
		{
			this->x = x;
			this->y = y;
		}
	};

	struct Color
	{
		//Use GLubyte to make the transfer faster
		//when we pass in the bytes to OpenGL what it's going to do is it's going to convert them into floats before our graphics cards uses them.
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;

		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}
	};

	struct UV
	{
		float u;
		float v;

		void setUV(float u, float v)
		{
			this->u = u;
			this->v = v;
		}
	};

	struct Vertex
	{
		//This is layed out exactly the same in memory as if we had a float position[2],
		//but doing it this way makes more sense.
		Position position;

		//4 bytes for r g b a color.
		Color color;

		//UV texture coordinates.
		UV uv;
		
	};
}